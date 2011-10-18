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
#include "../Entities/Creatures/Creature.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/EntityData.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Entities/Creatures/Player.hpp"
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
	mMap(random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 TilesetManager::get("office")),// @todo will there be other tilesets?  How should they be loaded?
	mViewport(viewport)
{
	// Configure the viewport.
	mViewport.setBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight()));
	mViewport.center(mPlayer);

	// Configure and setup the player.
	mPlayer->setPosition(mMap.getEntrance().x, mMap.getEntrance().y);
	mEntities.push_back(mPlayer);

	// Populate the map with traps/weapons/etc, but not within a 3 cell range of the player.
//@todo populate the map with traps/weapons/etc... - add this level as an event listener for the stuff (addEventListener(this))

	// Populate the map with enemies, but not within 3 cells of the player.
//@todo populate the map with enemies - add this level as an event listener for the enemies (addEventListener(this))

	// Focus the viewport on the player.
//	mFocusViewport(&player);@todo needed?
}

//Level::Level() :
//	mEData(mMap, levelData.entities, levelData.area_data),
//	mLightsQuad(levelData.light_quad_data),
//	mLightsElip(levelData.light_elip_data)
//{}

Level::~Level()
{
    // Delete any remaining actions.
    clearActions();

    // Remove the player from the entities list.
    mEntities.remove(mPlayer);

    // Now go through and delete the remaining level entities.
    for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++)
    	delete *it;
}

void Level::addChangeScoreListener(ChangeScoreListener* listener)
{
	mChangeScoreListeners.push_back(listener);
}

Entity* Level::checkEntityCollision(const Entity& entity) const
{
	for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++)
		if((*it)->getDimension().isIntersecting(entity.getDimension()))
			return *it;
	return 0;
}

bool Level::checkMapCollision(const Entity& entity) const
{
	return mMap.checkCollision(entity.getDimension());
}

void Level::draw(Renderer& renderer)
{
    // Draw the lower map.
    mMap.drawLower(renderer, mViewport);

    /* For the middle layer... */
    // First sort all entities based on their Z value (entities higher up (smaller y) come first).
    mEntities.sort(sortByZIndex);
    list<Entity*>::iterator current_entity = mEntities.begin();

    // Then draw the entities in a tile-y layer and then that tile-y layer itself.  Continue until all tile-y layers are drawn.
    unsigned int tile_height = mMap.getTileset().getHeight();
    for(unsigned int y = 0; y * tile_height != mMap.getHeight(); ++y)
    {
    	// Draw the map layer first.
    	mMap.drawMiddle(renderer, mViewport, (int)y);

    	// Then continue drawing any entities until we either reach the end of entities list or
    	// have drawn all entities between the current tile (y * tile_height) and the next ((y + 1) * tile_height).
    	for(; current_entity != mEntities.end() &&
    	      (*current_entity)->getDimension().vector.y + (*current_entity)->getDimension().height < (y + 1) * tile_height;
			  current_entity++)
    		(*current_entity)->draw(renderer);
    }

    // Draw the middle and upper map.
    mMap.drawUpper(renderer, mViewport);

    // Draw the lighting. @todo review lighting
//    mEData.drawLighting(renderer);
}

void Level::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	// Push on! Onwards to VICTORY!!!
	// ... or at least towards the GameScreen...
	pushEvent(event, content, creatureMovedToPointListener);
}

const Rectangle& Level::getExitArea() const
{
	return mMap.getExit();
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

		//@todo remove when done.
		if(input.isKeyPressed(SDLK_p))
		{
			for(list<ChangeScoreListener*>::iterator it = mChangeScoreListeners.begin(); it != mChangeScoreListeners.end(); it++)
				(*it)->changeScore(20);
		}

		if(input.isKeyPressed(SDLK_m))
		{
			for(list<ChangeScoreListener*>::iterator it = mChangeScoreListeners.begin(); it != mChangeScoreListeners.end(); it++)
				(*it)->changeScore(-5);
		}

		if(input.isKeyPressed(SDLK_b))
			mIsDone = true;
	}

	// Pass input to the player.
	mPlayer->handleInput(input);
}

bool Level::isDone() const
{
	return mIsDone;
}

void Level::logic()
{
    // Check for actions: If there is a current action set then activate it.
//    ActionInterface::logic(mEData); @todo review

    // Perform all being logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        (*it)->logic(*this);
    }

//    // Draw any static lights. @todo review
//	for(list<QuadData>::iterator it = mLightsQuad.begin(); it != mLightsQuad.end(); ++it)
//	{
//		mEData.addLight(it->area - offset);
//	}
//	for(list<ElipData>::iterator it = mLightsElip.begin(); it != mLightsElip.end(); ++it)
//	{
//		mEData.addLight(it->area - offset);
//	}

	// Perform viewport logic last.
	mViewport.logic();
}

void Level::playerFoundExit()
{
	mIsDone = true;
}

void Level::removeChangeScoreListener(ChangeScoreListener* listener)
{
	mChangeScoreListeners.remove(listener);
}
