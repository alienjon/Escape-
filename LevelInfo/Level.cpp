/*
 * Level.cpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#include "Level.hpp"

#include <cctype>
#include <stdexcept>

#include "../Math/Base64Functions.hpp"
#include "../Engine/Colors.hpp"
#include "../Entities/Creatures/Creature.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/EntityData.hpp"
#include "../Screens/GameScreen.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::invalid_argument;
using std::list;
using std::map;
using std::runtime_error;
using std::string;

//Level::Level(const MapRule& rule, Difficulty difficulty) :
//														   mMap(rule),
//														   mEData(mMap)
//{
//    // @todo need to implement auto-generated levels?
//}

Level::Level(const LevelData& levelData) :
	mName(levelData.name),
	mInitialPositions(levelData.entry_points),
	mMap(levelData.mapData),
	mEData(mMap, levelData.entities, levelData.area_data),
	mLightsQuad(levelData.light_quad_data),
	mLightsElip(levelData.light_elip_data)
{
	// Set the listeners.
	mEData.addEventListener(this);

	// Set the viewport bounds.
	mSetViewportBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight()));

	// @todo Need to be able to focus the viewport on an entity as a plot device.  Remove this once this is done.
	Entity* player = 0;
	for(list<Entity*>::const_iterator it = levelData.entities.begin(); it != levelData.entities.end(); ++it)
	{
		if((*it)->getName() == "Player")
		{
			player = *it;
			break;
		}
	}
	if(player)
	{
		mFocusViewport(player);
	}
	else
	{
		Logger::warn("Player not found.  Unable to focus the viewport on him.");
	}
}

Level::~Level()
{
    // Delete any remaining actions.
    clearActions();
}

void Level::addEntity(Entity* entity)
{
	mEData.addEntity(entity);
}

void Level::addMarker(const Vector& loc)
{
    mMarkersManager.addMarker(loc);
}

void Level::draw(Renderer& renderer)
{
	// If the map is smaller than the screen, then draw a black background.
	if(mMap.getWidth() < SCREEN_WIDTH || mMap.getHeight() < SCREEN_HEIGHT)
	{
		renderer.setColor(COLOR_BLACK);
		renderer.fillRectangle(Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

    // Draw the lower map.
    mMap.drawLower(renderer);

    // Draw the objects.
    mEData.draw(renderer);

    // Draw the middle and upper map.
    mMap.drawUpper(renderer);

    // Draw the lighting.
    mEData.drawLighting(renderer);

    // Draw the markers.
//    mMarkersManager.draw(renderer); @todo review
}

void Level::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	// Push on! Onwards to VICTORY!!!
	// ... or at least towards the GameScreen...
	pushEvent(event, content, creatureMovedToPointListener);
}

string Level::extractData() const
{
//    // Return the decoded information.
//	// @todo need to review loading and saving code.
//    return encodeBase64(mMap.extract()) + CHAR_DELIMITER + encodeBase64((mEData.extract())) +
//           CHAR_DELIMITER + encodeBase64(mTriggerManager.extract());
	return "";
}

const string& Level::getName() const
{
	return mName;
}

void Level::handleInput(const Input& input)
{
    // Check for level input.
	if(input.isKeyPressed(SDLK_F3))
	{
		mMarkersManager.clearMarkers();
		return;
    }

	// Pass input.
	mEData.handleInput(input);
}

void Level::levelFinished(bool next)
{
}

void Level::load(const Vector& playerPos)
{
	// Set all the positions.
	for(map<unsigned int, Vector>::iterator it = mInitialPositions.begin(); it != mInitialPositions.end(); ++it)
	{
		Entity* entity = mEData.getEntity(it->first);
		if(entity)
		{
			entity->setPosition(it->second.x, it->second.y);
		}
		else
		{
			Logger::log("Entity with ID '" + toString(it->first) + "' not found.");
		}
	}

	// Set the player's position.
	Entity* player = mEData.getEntity("Player");
	if(!player)
	{
		Logger::error("Cannot find the player when loading the level.");
	}
	else
	{
		player->setPosition(playerPos.x, playerPos.y);
	}

	// Push an 'area entered' plot event.
	pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_AREA_ENTERED + CHAR_DELIMITER_ALTERNATE + getName());
}

void Level::logic()
{
    // Check for actions: If there is a current action set then activate it.
    ActionInterface::logic(mEData);

	// Update the environment data before passing it to anything else.
	Vector offset = mGetViewportOffset();
	mEData.setOffset(offset);

    // Perform object logic.
    mEData.logic();

    // Draw any static lights.
	for(list<QuadData>::iterator it = mLightsQuad.begin(); it != mLightsQuad.end(); ++it)
	{
		mEData.addLight(it->area - offset);
	}
	for(list<ElipData>::iterator it = mLightsElip.begin(); it != mLightsElip.end(); ++it)
	{
		mEData.addLight(it->area - offset);
	}
}

void Level::removeEntity(const string& name)
{
	mEData.removeEntity(name);
}

void Level::unload()
{
	// Push an 'area exited' plot event.
	pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_AREA_EXITED + CHAR_DELIMITER_ALTERNATE + getName());
}
