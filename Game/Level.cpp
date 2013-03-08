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
#include "../Entities/Creature.hpp"
#include "../Entities/Entity.hpp"
#include "../Engine/FontManager.hpp"
#include "../Entities/KeyEntity.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"
#include "../Entities/Pickup.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/SpeedChange.hpp"
#include "../Entities/SurprisePickup.hpp"
#include "../Entities/TimeChange.hpp"

using std::invalid_argument;
using std::list;
using std::map;
using std::runtime_error;
using std::string;

const unsigned int FLOATINGTEXT_TIMER_INTERVAL = 15;
const float FLOATINGTEXT_MOVE_STEP = 0.3f;

Level::Level(unsigned int difficulty, Player& player) :
	mIsDone(false),
	mPlayer(player),
	mMap(random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2)),
		 random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2))),
	mPickupAward(false)
{
	// Start the timers.
	mFloatingTextTimer.start();

	// Calculate the entrance position.
	mPortal.setPosition((((mMap.getCellWidth() / 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getWidth() - (mPortal.getWidth() / 2),
						(((mMap.getCellHeight()/ 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getHeight() - (mPortal.getHeight() / 2));
	mPortal.addLevelCompleteListener(this);
	mEntities.push_back(&mPortal);

	// Configure and setup the player.
	mPlayer.setPosition((mPortal.getX() + (mPortal.getWidth()  / 2)) - (mPlayer.getWidth()  / 2),
						(mPortal.getY() + (mPortal.getHeight() / 2)) - (mPlayer.getHeight() / 2));
	mPlayer.addDeathListener(this);
	mPlayer.addChangeScoreListener(this);
	mPlayer.removeAllLocks();
	mEntities.push_back(&mPlayer);

	/*
	 * Set the initial locks on the player.
	 * @todo What if the timer counts down, if it reaches zero the player loses the
	 * level, but opening locks adds time (maybe for easy/medium?)
	 */
	sf::Color topLeft = sf::Color::Blue, topRight = sf::Color::Cyan, botLeft = sf::Color::Yellow, botRight = sf::Color::Green;
	mPortal.addLock(topLeft);
	mPortal.addLock(topRight);
	mPortal.addLock(botLeft);
	mPortal.addLock(botRight);

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
				entity = new KeyEntity(topLeft);
			else if(w == 0 && h == height - 1) // Top right corner.
				entity = new KeyEntity(topRight);
			else if(w == width - 1 && h == 0) // Bottom left corner.
				entity = new KeyEntity(botLeft);
			else if(w == width - 1 && h == height - 1) // Bottom right corner.
				entity = new KeyEntity(botRight);
			else if(w == width / 2 && h == height / 2) // Skip the portal cell.
			{}
			else
			{
				/**
				 * @todo Other items?
				 * @todo finalize colors
				 * @todo finalize which power ups I'm going to keep
				 */
				int n = random(1, 100);
				if(n <= 10)
					entity = new SurprisePickup(*this);
				else if(n <= 13)
				{
					entity = new Pickup(75, sf::Color::Magenta, Pickup::SMALL);
					mPickups.push_back(entity);
				}
				else if(n <= 20)
					entity = new Pickup(-50, sf::Color::Red, Pickup::LARGE);
				else if(n <= 23)
				{
					TimeChange* tmp = new TimeChange();
					tmp->addTimeChangeListener(this);
					entity = tmp;
				}
				else if(n <= 26)
					entity = new SpeedChange(0.5, mPlayer);
				else if(n <= 35)
					entity = new SpeedChange(1.75, mPlayer);
				else
				{
					entity = new Pickup(5, sf::Color::Magenta, Pickup::MEDIUM);
					mPickups.push_back(entity);
				}
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
	txt.setColor(color);
	txt.setPosition(position);
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
		if(*it != &entity && entity.getDimension().intersects((*it)->getDimension()))
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

void Level::draw(sf::RenderWindow& renderer)
{
	// Draw the map.
	renderer.draw(mMap);

	// Draw the entities.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
		(*it)->draw(renderer);

	// Draw the floating texts.
	for(list<sf::Text>::const_iterator it = mFloatingTexts.begin(); it != mFloatingTexts.end(); ++it)
		renderer.draw(*it);
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

void Level::logic(sf::View& camera, unsigned int delta)
{
	// Perform actions.
	ActionInterface::logic(*this);

	// Remove all dead entities.
	for(list<Entity*>::iterator it = mDeadEntities.begin(); it != mDeadEntities.end(); it++)
		mRemoveEntity(*it);
	mDeadEntities.clear();

    // Perform all entity logic.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
		(*it)->logic(*this, delta);

    // If all items have been picked up, display a floating text and give a bonus.
    if(mPickups.empty() && !mPickupAward)
    {
    	addFloatingText("Level Cleared!", mPlayer.getPosition(), sf::Color::Yellow, 30);
    	distributeChangeScore(250);
    	mPickupAward = true;
    }

    // Perform floating text logic if the interval is passed.
    //@todo turn floating text into actions?
    if(mFloatingTextTimer.getTime() >= FLOATINGTEXT_TIMER_INTERVAL)
    {
    	list<list<sf::Text>::iterator > removeList;
    	for(list<sf::Text>::iterator it = mFloatingTexts.begin(); it != mFloatingTexts.end(); ++it)
    	{
    		it->move(0, -FLOATINGTEXT_MOVE_STEP);
    		sf::Color c = it->getColor();
    		it->setColor(sf::Color(c.r, c.g, c.b, c.a - 3));
    		if(it->getColor().a == 0)
    			removeList.push_back(it);
    	}
    	for(list<list<sf::Text>::iterator >::iterator it = removeList.begin(); it != removeList.end(); ++it)
    		mFloatingTexts.erase(*it);
    	mFloatingTextTimer.start();
    }

	// Center the player on the screen.
	camera.setCenter(mPlayer.getX() + (mPlayer.getWidth() / 2), mPlayer.getY() + (mPlayer.getHeight() / 2));

	// Make sure that the camera doesn't go out of bounds.
	sf::Vector2f center = camera.getCenter(),
				 half(camera.getSize().x / 2, camera.getSize().y / 2);
	if(center.x - half.x < 0)
		center.x = half.x;
	if(center.x + half.x > mMap.getWidth())
		center.x = mMap.getWidth() - half.x;
	if(center.y - half.y < 0)
		center.y = half.y;
	if(center.y + half.y > mMap.getHeight())
		center.y = mMap.getHeight() - half.y;
	camera.setCenter(center);
}



void Level::playerFoundExit()
{
	mIsDone = true;
}

void Level::teleportPlayer()
{
	unsigned int x = random((unsigned int)1, mMap.getCellWidth() - 2),
				 y = random((unsigned int)1, mMap.getCellHeight()- 2);
	mPlayer.setPosition(((x * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getWidth(),
						((y * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getHeight());
	addFloatingText("Teleported!", mPlayer.getPosition(), sf::Color::Red, 20);
}
