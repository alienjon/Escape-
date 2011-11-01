/*
 * Level.cpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#include "Level.hpp"

#include <cctype>
#include <stdexcept>

#include "../Engine/Colors.hpp"
#include "../Entities/Creature.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/KeyEntity.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Portal.hpp"
#include "../Managers/TilesetManager.hpp"

using std::invalid_argument;
using std::list;
using std::map;
using std::runtime_error;
using std::string;

/**
 * The map's size is random based on the difficulty of the game.
 * The width and height is at least 5 + a range between the difficulty level
 * and 150% of the difficulty level.
 */
Level::Level(unsigned int difficulty, Player& player, Viewport& viewport) :
	mIsDone(false),
	mPlayer(&player),
	mPortal(new Portal()),
	mMap(random<unsigned int>(random<unsigned int>(difficulty, difficulty * 1.5),
							  random<unsigned int>(difficulty, difficulty * 1.5)),
		 random<unsigned int>(random<unsigned int>(difficulty, difficulty * 1.5),
							  random<unsigned int>(difficulty, difficulty * 1.5))),
	mViewport(viewport)
{
	// Configure the viewport.
	mViewport.setBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight())); // @todo should this be set here or in gamescreen?
	mViewport.center(mPlayer);

	// Configure and setup the portal.
	mPortal->setPosition(mMap.getPortal().x - (mPortal->getWidth() / 2), mMap.getPortal().y - (mPortal->getHeight() / 2));
	mPortal->addLevelCompleteListener(this);
	mEntities.push_back(mPortal);

	// Configure and setup the player.
	mPlayer->setPosition(mMap.getPortal().x - (mPlayer->getWidth() / 2), mMap.getPortal().y - (mPlayer->getHeight() / 2));
	mPlayer->addDeathListener(this);
	mPlayer->addChangeScoreListener(this);
	mEntities.push_back(mPlayer);

	//@todo randomize the colors and the color's positions in the map.
	// Set the initial locks on the player.@review Might locks be added later?  What if the timer counts down, if it reaches zero the player loses the level, but opening locks adds time (maybe for easy/medium?)
	mPortal->addLock(COLOR_RED);
	mPortal->addLock(COLOR_BLUE);
	mPortal->addLock(COLOR_ORANGE);
	mPortal->addLock(COLOR_GREEN);

	unsigned int x_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getWidth(),
				 y_offset = (MAP_CELL_SIDE / 2) * mMap.getTileset().getHeight();

	KeyEntity* key = new KeyEntity(COLOR_RED);
	key->setPosition(x_offset - (key->getWidth() / 2), y_offset - (key->getHeight() / 2)); // Top left corner.
	mAddEntity(key);
	key = new KeyEntity(COLOR_BLUE);
	key->setPosition(mMap.getWidth() - x_offset - (key->getWidth() / 2), y_offset - (key->getHeight() / 2)); // Top right corner.
	mAddEntity(key);
	key = new KeyEntity(COLOR_ORANGE);
	key->setPosition(x_offset - (key->getWidth() / 2), mMap.getHeight() - y_offset - (key->getHeight() / 2)); // Bottom left corner.
	mAddEntity(key);
	key = new KeyEntity(COLOR_GREEN);
	key->setPosition(mMap.getWidth() - x_offset - (key->getWidth() / 2), mMap.getHeight() - y_offset - (key->getHeight() / 2)); // Bottom right corner.
	mAddEntity(key);

	// Populate the map with traps/weapons/etc, but not within a 3 cell range of the player.
//@todo populate the map with traps/weapons/etc... - add this level as an event listener for the stuff (addEventListener(this))

	// Populate the map with enemies, but not within 3 cells of the player.
//@todo populate the map with enemies - add this level as an event listener for the enemies (addEventListener(this))
}

Level::~Level()
{
    // Delete any remaining actions.
    clearActions();

    // Remove the player from the entities list.
    mEntities.remove(mPlayer);
    mPlayer->removeDeathListener(this);
    mPlayer->removeChangeScoreListener(this);
    mPortal->removeLevelCompleteListener(this);
    mEntities.remove(mPortal);
    delete mPortal;

    // Now go through and delete the remaining level entities.
    while(!mEntities.empty())
    {
    	mRemoveEntity(*(mEntities.begin()));
    }
}

void Level::mAddEntity(Entity* entity)
{
	entity->addDeathListener(this);
	entity->addChangeScoreListener(this);
	entity->addAddLockListener(mPlayer);
	entity->addRemoveLockListener(mPortal);
	mEntities.push_back(entity);
}

void Level::mRemoveEntity(Entity* entity)
{
	entity->removeDeathListener(this);
	entity->removeChangeScoreListener(this);
	entity->removeAddLockListener(mPlayer);
	entity->removeRemoveLockListener(mPortal);
	mEntities.remove(entity);
	delete entity;
}

void Level::changeScore(int change)
{
	distributeChangeScore(change);
}

Entity* Level::checkEntityCollision(const Entity& entity) const
{
	// If this is the player, check for a portal collision first.
	for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++)
		if(*it != &entity && entity.getDimension().isIntersecting((*it)->getDimension()))
			return *it;
	return 0;
}

bool Level::checkMapCollision(const Entity& entity) const
{
	return mMap.checkCollision(entity.getDimension());
}

void Level::draw(Renderer& renderer)
{
	// Draw a black ground.
	renderer.setColor(COLOR_BLACK);
	renderer.fillRectangle(gcn::Rectangle(mViewport.getX(), mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

	// Draw the map.
	mMap.draw(renderer, mViewport);

	// This is the entrance point.
	mPortal->draw(renderer);

	// Draw the entities.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
		(*it)->draw(renderer);
}

const Vector& Level::getPortal() const
{
	return mMap.getPortal();
}

const Map& Level::getMap() const
{
	return mMap;
}

const Viewport& Level::getViewport() const
{
	return mViewport;
}

void Level::handleInput(const Input& input)
{
	if(Game::isDebug())
	{
		if(input.isKeyPressed(SDLK_t))
		{
			if(mViewport.isTracking())
			{
				mViewport.center(0);
				Logger::log("Player tracking deactivated");
			}
			else
			{
				mViewport.center(mPlayer);
				Logger::log("Player tracking activated");
			}
		}

		if(!mViewport.isTracking())
		{
			int step = 25;
			if(input.isKeyPressed(SDLK_UP))
				mViewport.setY(mViewport.getY() - step);
			if(input.isKeyPressed(SDLK_DOWN))
				mViewport.setY(mViewport.getY() + step);
			if(input.isKeyPressed(SDLK_LEFT))
				mViewport.setX(mViewport.getX() - step);
			if(input.isKeyPressed(SDLK_RIGHT))
				mViewport.setX(mViewport.getX() + step);
		}

		if(input.isKeyPressed(SDLK_b))//@todo remove when done testing
			mIsDone = true;
	}

	// Pass input to the player.
	mPlayer->handleInput(input);
}

bool Level::isDone() const
{
	return mIsDone;
}

void Level::levelComplete()
{
	mIsDone = true;
}

void Level::logic()
{
	// Remove all dead enities.
	for(list<Entity*>::iterator it = mDeadEntities.begin(); it != mDeadEntities.end(); it++)
	{
		mRemoveEntity(*it);
	}
	if(!mDeadEntities.empty())// Clear the dead entities if there are any in the list.
		mDeadEntities.clear();

    // Perform all being logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
        (*it)->logic(*this);

	// Perform viewport logic last.sssss
	mViewport.logic();
}

void Level::playerFoundExit()
{
	mIsDone = true;
}
