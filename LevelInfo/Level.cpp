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
Level::Level(unsigned int difficulty, Player& player) :
	mPlayer(&player),
	mMap(random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 random<unsigned int>(5 + random<unsigned int>(difficulty, difficulty * 1.5),
							  5 + random<unsigned int>(difficulty, difficulty * 1.5)),
		 TilesetManager::get("office"))// @todo will there be other tilesets?  How should they be loaded?
{
	// Place the player in the entrance.
//@todo place the player

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
}

void Level::draw(Renderer& renderer, const Viewport& viewport)
{
	// If the map is smaller than the screen, then draw a black background.
	if(mMap.getWidth() < SCREEN_WIDTH || mMap.getHeight() < SCREEN_HEIGHT)
	{
		renderer.setColor(COLOR_BLACK);
		renderer.fillRectangle(Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

    // Draw the lower map.
    mMap.drawLower(renderer, viewport);

    // Draw the middle map.
    mMap.drawMiddle(renderer, viewport);

    // Draw the objects.
//    mEData.draw(renderer);

    // Draw the middle and upper map.
    mMap.drawUpper(renderer, viewport);

    // Draw the lighting.
//    mEData.drawLighting(renderer);
}

void Level::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	// Push on! Onwards to VICTORY!!!
	// ... or at least towards the GameScreen...
	pushEvent(event, content, creatureMovedToPointListener);
}

void Level::handleInput(const Input& input)
{
	// Pass input to each entity.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
	{
		(*it)->handleInput(input);
	}
}

void Level::levelFinished(bool next)
{
}

void Level::load()
{
	// Set the viewport bounds.
	mSetViewportBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight()));
}

void Level::logic()
{
    // Check for actions: If there is a current action set then activate it.
//    ActionInterface::logic(mEData); @todo review

	// Update the environment data before passing it to anything else.
//	Vector offset = mGetViewportOffset(); @todo review
//	mEData.setOffset(offset); @todo review

    // Perform all being logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
//        (*it)->logic(*this);@todo Should the entities access the level in this way?
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
}
