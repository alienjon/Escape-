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

const gcn::Color LEVEL_COLOR_BACKGROUND = gcn::Color(0, 0, 0);// @fixme What color do I want?
const gcn::Color LEVEL_COLOR_PORTAL		= gcn::Color(0, 0, 255);// @fixme What color do I want?

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
							  5 + random<unsigned int>(difficulty, difficulty * 1.5))),
	mViewport(viewport)
{
	// Configure the viewport.
	mViewport.setBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight())); // @todo should this be set here or in gamescreen?
	mViewport.center(mPlayer);

	// Configure and setup the player.
	mPlayer->setPosition(mMap.getPortal().x - (mPlayer->getWidth() / 2), mMap.getPortal().y - (mPlayer->getHeight() / 2));
	mEntities.push_back(mPlayer);

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
	// Draw a black ground.
	renderer.setColor(LEVEL_COLOR_BACKGROUND);
	renderer.fillRectangle(gcn::Rectangle(mViewport.getX(), mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

	// Draw the map.
	mMap.draw(renderer, mViewport);

	// This is the entrance point. @todo Review how this appears/functions.
	renderer.setColor(LEVEL_COLOR_PORTAL);
	renderer.fillRectangle(Rectangle(mMap.getPortal().x - 20, mMap.getPortal().y - 20, 40, 40));
	renderer.setColor(LEVEL_COLOR_BACKGROUND);
	renderer.fillRectangle(Rectangle(mMap.getPortal().x - 15, mMap.getPortal().y - 15, 30, 30));

	// Draw the entities.
	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
		(*it)->draw(renderer);
}

void Level::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	// Push on! Onwards to VICTORY!!!
	// ... or at least towards the GameScreen...
	pushEvent(event, content, creatureMovedToPointListener);
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

void Level::logic()
{
    // Perform all being logic.
    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
        (*it)->logic(*this);

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
