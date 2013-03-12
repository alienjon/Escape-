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
	mMap(difficulty, difficulty),
	mPickupAward(false)
{
	// Start the timers.
	mFloatingTextTimer.start();

	// Calculate the entrance position.
	mPortal.addLevelCompleteListener(this);
	mEntities.push_back(&mPortal);

	// Configure and setup the player.
	mPlayer.addDeathListener(this);
	mPlayer.addChangeScoreListener(this);
	mEntities.push_back(&mPlayer);

	// Configure and setup the key.
	KeyEntity* key = new KeyEntity();


	// Populate the map with entities, etc...
	unsigned int width = mMap.getCellWidth(),
				 height= mMap.getCellHeight(),
				 x_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getWidth(),
				 y_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getHeight();

	// First, place the portal at a random location.
	int portal_x = random((unsigned int)0, width), portal_y = random((unsigned int)0, height);
	mPortal.setPosition(portal_x * MAP_CELL_SIDE * mMap.getTileset().getWidth() + x_offset,
						portal_y * MAP_CELL_SIDE * mMap.getTileset().getHeight()+ y_offset);

	// Next, place the player at a random starting location.
	int player_x = random((unsigned int)0, width), player_y = random((unsigned int)0, height);
	mPlayer.setPosition(player_x * MAP_CELL_SIDE * mMap.getTileset().getWidth() + x_offset,
						player_y * MAP_CELL_SIDE * mMap.getTileset().getHeight()+ y_offset);

	// Next, place the key at a random location.
	key->setPosition(0, 0);
	int key_x = random((unsigned int)0, width), key_y = random((unsigned int)0, height);

	// Finally, populate the rest of the map with stuff.
	for(unsigned int h = 0; h != height; ++h)
	{
		for(unsigned int w = 0; w != width; ++w)
		{
			// If the current cell currently holds either the portal, player's starting location, or key, then continue in the loop.
			if((w == portal_x && h == portal_y) ||
			   (w == player_x && h == player_y) ||
			   (w == key_x    && h == key_y))
				continue;

			// Get the x and y locations for this entity.
			int x = (w * MAP_CELL_SIDE * mMap.getTileset().getWidth()) + x_offset,
				y = (h * MAP_CELL_SIDE * mMap.getTileset().getHeight()) + y_offset;

			// A likely entity to be created.
			Entity* entity = 0;
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
	entity->addFloatingTextListener(this);
	mEntities.push_back(entity);
}

void Level::mRemoveEntity(Entity* entity)
{
	mPickups.remove(entity);
	entity->removeDeathListener(this);
	entity->removeChangeScoreListener(this);
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
