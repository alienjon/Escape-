/*
 * Level.cpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#include "Level.hpp"

#include <cctype>
#include <stdexcept>

#include "../Entities/Entity.hpp"
#include "../Engine/FontManager.hpp"
#include "../Game/Game.hpp"
#include "../Entities/KeyEntity.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Entities/Pickup.hpp"
#include "../Entities/Player.hpp"

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
	mPortal(30, 30),
	mMap(random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2)),
		 random(random(difficulty, difficulty * 2), random(difficulty, difficulty * 2)))
{
	// Start the floating text timer.
	mFloatingTextTimer.start();

	// Calculate the entrance position.
	mPortal.setPosition((((mMap.getCellWidth() / 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getWidth() - (mPortal.getPortalWidth() / 2),
						(((mMap.getCellHeight()/ 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mMap.getTileset().getHeight() - (mPortal.getPortalHeight() / 2));
	if(Game::isDebug())
		Logger::log("Portal(" + toString((mPortal.getX() * 2) / mMap.getTileset().getWidth() / MAP_CELL_SIDE) + ", " +
					toString((mPortal.getY() * 2) / mMap.getTileset().getHeight() / MAP_CELL_SIDE) + ")");
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
				//@todo Add pickups that increase time, decrease score, other effects?
				if(random(1, 20) == 1)
					entity = new Pickup(50, sf::Color::White, 15);
				else
					entity = new Pickup(5, sf::Color::Magenta, 8);
			}

			// If an entity was created, configure it.
			if(entity)
			{
				entity->setPosition(x, y);
				mAddEntity(entity);
			}
		}
	}

	// Populate the map with enemies, but not within 3 cells of the player.
//@todo populate the map with enemies - add this level as an event listener for the enemies (addEventListener(this))
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
	entity->removeDeathListener(this);
	entity->removeChangeScoreListener(this);
	entity->removeAddLockListener(&mPlayer);
	entity->removeRemoveLockListener(&mPortal);
	entity->removeFloatingTextListener(this);
	mEntities.remove(entity);
	delete entity;
}

void Level::addFloatingText(const string& str, const sf::Vector2f& position, const sf::Color& color)
{
	sf::Text txt = sf::Text(str, FontManager::getSFFont(FONT_CAPTION), 20);
	txt.SetColor(color);
	txt.SetPosition(position);
	mFloatingTexts.push_back(txt);
}

void Level::changeScore(int change)
{
	distributeChangeScore(change);
}

Entity* Level::checkEntityCollision(const Entity& entity) const
{
	// If this is the player, check for a portal collision first.
	for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++)
		if(*it != &entity && isPolyIntersecting(entity.getDimension(), (*it)->getDimension()))
			return *it;
	return 0;
}

bool Level::checkMapCollision(const Entity& entity) const
{
	return mMap.checkCollision(entity.getDimension());
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
	// Remove all dead enities.
	for(list<Entity*>::iterator it = mDeadEntities.begin(); it != mDeadEntities.end(); it++)
		mRemoveEntity(*it);
	mDeadEntities.clear();

    // Perform all being logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
        (*it)->logic(*this);

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

	// Make sure that the camera doesn't go out of bounds.@fixme The camera is going out of bounds...
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
