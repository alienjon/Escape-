/*
 * Level.cpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#include "Level.hpp"

#include <cctype>
#include <stdexcept>

#include "../Engine/AudioManager.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/FlipScreen.hpp"
#include "../Engine/FontManager.hpp"
#include "../Entities/KeyEntity.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"
#include "../Entities/Phase.hpp"
#include "../Entities/Pickup.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/SpeedChange.hpp"
#include "../Entities/Teleporter.hpp"
#include "../Entities/TimeChange.hpp"
#include "../Entities/ZoomScreen.hpp"

using std::invalid_argument;
using std::list;
using std::map;
using std::runtime_error;
using std::string;

const unsigned int FLOATINGTEXT_TIMER_INTERVAL = 15;
const float FLOATINGTEXT_MOVE_STEP = 0.3f;
const unsigned int FLIP_ROTATION_SPEED = 5;
const float FLIP_ROTATION_STEP = 1.5f;
const unsigned int ZOOM_SPEED = 5;
const float ZOOM_STEP = 0.0055f;

Level::Level(unsigned int difficulty, Player& player) :
	mIsDone(false),
	mPlayer(player),
	mPortal(30, 30),
	mMap(random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2)),
		 random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2))),
	mPickupAward(false),
	mFlipAngle(0.f),
	mFlipped(false),
	mZoomFactor(1.f),
	mZoomed(false),
	mTeleportInterval(0),
	mTeleportIntervalMin(45000),//@todo implement a way to dynamically configure the teleport intervals (maybe a leveldata object?)
	mTeleportIntervalMax(90000)
{
	// Start the timers.
	mFloatingTextTimer.start();
	mTeleportTimer.start();

	// Set the initial teleport interval.
	mTeleportInterval = random(mTeleportIntervalMin, mTeleportIntervalMax);

	// Calculate the entrance position.
	mPortal.setPosition((((mMap.getCellWidth() / 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getWidth() - (mPortal.getPortalWidth() / 2),
						(((mMap.getCellHeight()/ 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getHeight() - (mPortal.getPortalHeight() / 2));
	mPortal.addLevelCompleteListener(this);
	mEntities.push_back(&mPortal);

	// Configure and setup the player.
	mPlayer.setPosition((mPortal.getX() + (mPortal.getPortalWidth()  / 2)) - (mPlayer.getWidth()  / 2),
						(mPortal.getY() + (mPortal.getPortalHeight() / 2)) - (mPlayer.getHeight() / 2));
	mPlayer.addDeathListener(this);
	mPlayer.addChangeScoreListener(this);
	mPlayer.removeAllLocks();
	mEntities.push_back(&mPlayer);

	/*
	 * Set the initial locks on the player.
	 * @note What if the timer counts down, if it reaches zero the player loses the
	 * level, but opening locks adds time (maybe for easy/medium?)
	 */
	mPortal.addLock(sf::Color::Red);
	mPortal.addLock(sf::Color::Cyan);
	mPortal.addLock(sf::Color::Yellow);
	mPortal.addLock(sf::Color::Green);

	// Populate the map with entities, etc...
	unsigned int width = mMap.getCellWidth(),
				 height= mMap.getCellHeight(),
				 x_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getWidth(),
				 y_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getHeight();
	for(unsigned int h = 0; h != height; ++h)
	{
		for(unsigned int w = 0; w != width; ++w)
		{
			// Get the x and y locations for this entity.
			int x = (w * MAP_CELL_SIDE * mMap.getTileset().getWidth()) + x_offset,
				y = (h * MAP_CELL_SIDE * mMap.getTileset().getHeight()) + y_offset;

			// A likely entity to be created.
			Entity* entity = 0;

			// If this is one of the 4 corners, add a key.
			if(w == 0 && h == 0) // Top left corner.
				entity = new KeyEntity(sf::Color::Red);
			else if(w == 0 && h == height - 1) // Top right corner.
				entity = new KeyEntity(sf::Color::Cyan);
			else if(w == width - 1 && h == 0) // Bottom left corner.
				entity = new KeyEntity(sf::Color::Yellow);
			else if(w == width - 1 && h == height - 1) // Bottom right corner.
				entity = new KeyEntity(sf::Color::Green);
			else if(w == width / 2 && h == height / 2) // Skip the portal cell.
			{}
			else // Add a point pickup
			{
				// A 1 in 10 chance that the pickup will be a big one.
				/**
				 * @todo review the percentages (change them based on the size of the map/difficulty?)
				 *
				 * @todo implement pickups for the player: things the player can pickup (up to 3) and an icon will display
				 * on the side of the screen.  If the player hits the spacebar then these items are used (or holds
				 * shift then the center item is highlighted. or a left press (with the spacebar) or right press will
				 * select the item to the left or right - pressing that direction and holding it highlights that option, releasing
				 * the button returns to the center and pressing the opposite direction will center the selection)
				 * Examples: 'shift' - shift the player one cell in the specified direction - when the item is activated (the
				 * player presses spacebar) 4 directional arrows appear in the GUI (surrounding the player, one in each direction)
				 * the player then presses that direction and the player shrinks completely and then its position is set to
				 * the middle of once cell in the direction specified by the player.
				 */
				int n = random(1, 100);
				if(n <= 65)
				{
					entity = new Pickup(5, sf::Color::Magenta, 20);
					mPickups.push_back(entity);
				}
				else if(n <= 70)
				{
					entity = new Pickup(25, sf::Color::Magenta, 5);
					mPickups.push_back(entity);
				}
				else if(n <= 75)
					entity = new TimeChange(*this);
				else if(n <= 80)
					entity = new SpeedChange(2.f, mPlayer);
				else if(n <= 85)
					entity = new SpeedChange(0.5f, mPlayer);
				else if(n <= 90)
					entity = new Pickup(-50, sf::Color::Red, 50);
				else if(n <= 95)
					entity = new FlipScreen(*this);
				else
					entity = new ZoomScreen(*this);
			}

			// If an entity was created, configure it.
			if(entity)
			{
				entity->setPosition(x, y);
				mAddEntity(entity);
			}
		}
	}
}

Level::~Level()
{
    // Delete any remaining actions.
    clearActions();

    // Remove the player from the entities list.
    mEntities.remove(&mPlayer);
    mPlayer.removeDeathListener(this);
    mPlayer.removeChangeScoreListener(this);
    mPortal.removeLevelCompleteListener(this);
    mEntities.remove(&mPortal);

    // Now go through and delete the remaining level entities.
    while(!mEntities.empty())
    	mRemoveEntity(*(mEntities.begin()));
}

void Level::mAddEntity(Entity* entity)
{
	entity->addDeathListener(this);
	entity->addChangeScoreListener(this);
	entity->addAddLockListener(&mPlayer);
	entity->addRemoveLockListener(&mPortal);
	entity->addFloatingTextListener(this);
	mEntities.push_back(entity);
}

void Level::mRemoveEntity(Entity* entity)
{
	mPickups.remove(entity);
	entity->removeDeathListener(this);
	entity->removeChangeScoreListener(this);
	entity->removeAddLockListener(&mPlayer);
	entity->removeRemoveLockListener(&mPortal);
	entity->removeFloatingTextListener(this);
	mEntities.remove(entity);
	delete entity;
}

void Level::addFloatingText(const string& str, const sf::Vector2f& position, const sf::Color& color, unsigned int size)
{
	sf::Text txt = sf::Text(str, FontManager::getSFFont(FONT_DEFAULT), size);
	txt.SetColor(color);
	txt.SetPosition(position);
	mFloatingTexts.push_back(txt);
}

void Level::changeScore(int change)
{
	distributeChangeScore(change);
}

bool Level::checkEntityCollision(Entity& entity)
{
	bool collision = false;
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
		if(*it != &entity && isPolyIntersecting(entity.getDimension(), (*it)->getDimension()))
		{
			// If both entities are collidable, then a collision occurred.
			if(entity.isCollidable() && (*it)->isCollidable())
				collision = true;

			// If both entities are interactable then have the moving entity collide.
			if(entity.isInteractable() && (*it)->isInteractable())
				entity.collide(*(*it));
		}
	return collision;
}

bool Level::checkMapCollision(Entity& entity)
{
	return entity.isCollidable() && mMap.checkCollision(entity.getDimension());
}

void Level::draw(gcn::SFMLGraphics& renderer)
{
	// Draw a black ground.
	renderer.Clear(sf::Color::Black);

	// Draw the map.
	mMap.draw(renderer);

	// Draw the entities.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
		(*it)->draw(renderer);

	// Draw the floating texts.
	for(list<sf::Text>::const_iterator it = mFloatingTexts.begin(); it != mFloatingTexts.end(); ++it)
		renderer.Draw(*it);
}

void Level::flip()
{
	mFlipTimer.start();
}

const Map& Level::getMap() const
{
	return mMap;
}

bool Level::isDone() const
{
	return mIsDone;
}

void Level::levelComplete()
{
	mIsDone = true;
}

void Level::logic(sf::View& camera)
{
	// Remove all dead entities.
	for(list<Entity*>::iterator it = mDeadEntities.begin(); it != mDeadEntities.end(); it++)
		mRemoveEntity(*it);
	mDeadEntities.clear();

    // Perform all entity logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
        (*it)->logic(*this);

    // If all items have been picked up, display a floating text and give a bonus.
    if(mPickups.empty() && !mPickupAward)
    {
    	addFloatingText("Level Cleared!", mPlayer.getPosition(), sf::Color::Yellow, 30);
    	distributeChangeScore(250);
    	mPickupAward = true;
    }

    // Perform floating text logic if the interval is passed.
    if(mFloatingTextTimer.getTime() >= FLOATINGTEXT_TIMER_INTERVAL)
    {
    	list<list<sf::Text>::iterator > removeList;
    	for(list<sf::Text>::iterator it = mFloatingTexts.begin(); it != mFloatingTexts.end(); ++it)
    	{
    		it->Move(0, -FLOATINGTEXT_MOVE_STEP);
    		sf::Color c = it->GetColor();
    		it->SetColor(sf::Color(c.r, c.g, c.b, c.a - 3));
    		if(it->GetColor().a == 0)
    			removeList.push_back(it);
    	}
    	for(list<list<sf::Text>::iterator >::iterator it = removeList.begin(); it != removeList.end(); ++it)
    		mFloatingTexts.erase(*it);
    	mFloatingTextTimer.start();
    }

	// Flip the screen.
	if(mFlipTimer.isStarted() && mFlipTimer.getTime() >= FLIP_ROTATION_SPEED)
	{
		mFlipAngle += FLIP_ROTATION_STEP;
		mFlipTimer.start();
		if(mFlipped && mFlipAngle >= 360.f)
		{
			mFlipTimer.stop();
			mFlipAngle = 0.f;
			mFlipped = false;
		}
		else if(!mFlipped && mFlipAngle >= 180.f)
		{
			mFlipTimer.stop();
			mFlipAngle = 180.f;
			mFlipped = true;
		}
		camera.SetRotation(mFlipAngle);
	}

	// Zoom the screen.
	if(mZoomTimer.isStarted() && mZoomTimer.getTime() >= ZOOM_SPEED)
	{
		mZoomFactor *= 1.f - (ZOOM_STEP * (mZoomed ? -1.f : 1.f));
		if(mZoomed && mZoomFactor >= 1.f)
		{
			mZoomTimer.stop();
			mZoomFactor = 1.f;
			mZoomed = false;
		}
		else if(!mZoomed && mZoomFactor <= 0.3f)
		{
			mZoomTimer.stop();
			mZoomFactor = 0.3f;
			mZoomed = true;
		}
		else
			camera.Zoom(1.f - (ZOOM_STEP * (mZoomed ? -1.f : 1.f)));
	}

	// Check to see if a new teleporter is to be created.
	if(mTeleportTimer.getTime() >= mTeleportInterval)
	{
		// Play a warning sound that a teleporter was created.
		AudioManager::playSound(SOUND_TELEPORT_WARNING);
		// Create the new teleporter on a random side and have it move to the opposite side.
		Teleporter* tele = 0;
		switch(random(0, 3))
		{
			case 0: // Move Up
			{
				tele = new Teleporter(mMap.getWidth(), 4, *this);
				tele->setPosition(0, mMap.getHeight());
				tele->addWaypoint(sf::Vector2f(0, 0));
				break;
			}
			case 1: // Move Down
			{
				tele = new Teleporter(mMap.getWidth(), 4, *this);
				tele->setPosition(0, 0);
				tele->addWaypoint(sf::Vector2f(0, mMap.getHeight()));
				break;
			}
			case 2: // Move Left
			{
				tele = new Teleporter(4, mMap.getHeight(), *this);
				tele->setPosition(mMap.getWidth(), 0);
				tele->addWaypoint(sf::Vector2f(0, 0));
				break;
			}
			default: // Move Right
			{
				tele = new Teleporter(4, mMap.getHeight(), *this);
				tele->setPosition(0, 0);
				tele->addWaypoint(sf::Vector2f(mMap.getWidth(), 0));
			}
		}
		mAddEntity(tele);

		// Restart the timer and reset the teleport interval.
		mTeleportTimer.start();
		mTeleportInterval = random(mTeleportIntervalMin, mTeleportIntervalMax);
	}

	// Center the player on the screen.
	camera.SetCenter(mPlayer.getX() + (mPlayer.getWidth() / 2), mPlayer.getY() + (mPlayer.getHeight() / 2));

	// Make sure that the camera doesn't go out of bounds.
	sf::Vector2f center = camera.GetCenter(),
				 half(camera.GetSize().x / 2, camera.GetSize().y / 2);
	if(center.x - half.x < 0)
		center.x = half.x;
	if(center.x + half.x > mMap.getWidth())
		center.x = mMap.getWidth() - half.x;
	if(center.y - half.y < 0)
		center.y = half.y;
	if(center.y + half.y > mMap.getHeight())
		center.y = mMap.getHeight() - half.y;
	camera.SetCenter(center);
}

void Level::playerFoundExit()
{
	mIsDone = true;
}

void Level::teleportPlayer()
{
	unsigned int x = random((unsigned int)1, mMap.getCellWidth() - 2),
				 y = random((unsigned int)1, mMap.getCellHeight()- 2);
	mPlayer.setPosition(((x * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getWidth() - (mPlayer.getWidth() / 2),
						((y * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getHeight() - (mPlayer.getHeight() / 2));
	checkEntityCollision(mPlayer);
	addFloatingText("Teleported!", mPlayer.getPosition(), sf::Color::Red, 20);
}

void Level::zoom()
{
	mZoomTimer.start();
}
