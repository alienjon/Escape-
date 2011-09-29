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
#include "../Screens/GameScreen.hpp"
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
Level::Level(unsigned int difficulty, Player& player, GameScreen* parent) :
	mIsDone(false),
	mPlayer(&player),
	mMap(random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 TilesetManager::get("office")),// @todo will there be other tilesets?  How should they be loaded?
	mGameScreen(parent)
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
	mFocusViewport(&player);
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
    // Everything on the level is relative to the viewport.
	renderer.pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

	// If the map is smaller than the screen, then draw a black background.
	if(mMap.getWidth() < SCREEN_WIDTH || mMap.getHeight() < SCREEN_HEIGHT)
	{
		renderer.setColor(COLOR_BLACK);
		renderer.fillRectangle(Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

    // Draw the lower map.
    mMap.drawLower(renderer, mViewport);

    // Draw the middle map.
    mMap.drawMiddle(renderer, mViewport);

    // Draw the entities.
    for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); it++)
    	(*it)->draw(renderer);

    // Draw the middle and upper map.
    mMap.drawUpper(renderer, mViewport);

    // Draw the lighting.
//    mEData.drawLighting(renderer);

    // Pop the drawing area.
    renderer.popClipArea();

    // Apply the layers.
//    renderer.applyLayers();@todo review lighting
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

const Vector Level::getViewportOffset() const
{
	return mViewport.getOffset();
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
			{
				mViewport.setY(mViewport.getY() - step);
			}
			if(input.isKeyPressed(SDLK_DOWN))
			{
				mViewport.setY(mViewport.getY() + step);
			}
			if(input.isKeyPressed(SDLK_LEFT))
			{
				mViewport.setX(mViewport.getX() - step);
			}
			if(input.isKeyPressed(SDLK_RIGHT))
			{
				mViewport.setX(mViewport.getX() + step);
			}
		}
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
