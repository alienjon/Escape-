/*
 * Tileset.cpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */
#include "Tileset.hpp"

#include <stdexcept>

#include "../main.hpp"
#include "../Engine/VideoManager.hpp"

using std::map;
using std::runtime_error;
using std::string;

Tileset::Tileset(const string& filename)
{
	// Calculate the width and height.
	sf::Sprite meta = sf::Sprite(VideoManager::getTexture(filename));
	mWidth  = meta.getLocalBounds().width / 3;
	mHeight = meta.getLocalBounds().height / 3;

	// Create the map areas.
	mTiles[NORTHWEST] = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[NORTHWEST].setTextureRect(sf::IntRect(0, 0, mWidth, mHeight));

	mTiles[NORTH]	  = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[NORTH].setTextureRect(sf::IntRect(mWidth, mHeight * 2, mWidth, mHeight));

	mTiles[NORTHEAST] = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[NORTHEAST].setTextureRect(sf::IntRect(mWidth * 2, 0, mWidth, mHeight));

	mTiles[WEST]	  = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[WEST].setTextureRect(sf::IntRect(0, mHeight, mWidth, mHeight));

	mTiles[EAST]	  = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[EAST].setTextureRect(sf::IntRect(mWidth * 2, mHeight, mWidth, mHeight));

	mTiles[SOUTHWEST] = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[SOUTHWEST].setTextureRect(sf::IntRect(0, mHeight * 2, mWidth, mHeight));

	mTiles[SOUTH]	  = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[SOUTH].setTextureRect(sf::IntRect(mWidth, 0, mWidth, mHeight));

	mTiles[SOUTHEAST] = sf::Sprite(VideoManager::getTexture(filename));
	mTiles[SOUTHEAST].setTextureRect(sf::IntRect(mWidth * 2, mHeight * 2, mWidth, mHeight));

	mTiles[EMPTYFLOOR]= sf::Sprite(VideoManager::getTexture(filename));
	mTiles[EMPTYFLOOR].setTextureRect(sf::IntRect(0, 0, 0, 0));

	/* Create the collision areas based on the width of the collision area. */
	int col_size = 8; // @todo Should this be fixed or set with the tileset?
	// The empty floor.
	CollisionArea area;
	mCollisions[EMPTYFLOOR]= area;
	sf::FloatRect rect;

	// The north wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[NORTH] = area;

	// The south wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[SOUTH] = area;

	// The west wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[WEST] = area;

	// The east wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[EAST] = area;

	// The northwest wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHWEST] = area;

	// The northeast wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHEAST] = area;

	// The southeast wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHEAST] = area;

	// The southwest wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHWEST] = area;
}

const sf::Sprite& Tileset::getTile(Tileset::TileType type) const
{
	map<Tileset::TileType, sf::Sprite>::const_iterator it = mTiles.find(type);
	if(it == mTiles.end())
		throw runtime_error("Tileset::getTile() -> Invalid tile type provided.");
	return it->second;
}

const CollisionArea& Tileset::getTileCollision(Tileset::TileType type) const
{
	map<Tileset::TileType, CollisionArea>::const_iterator it = mCollisions.find(type);
	if(it == mCollisions.end())
		throw runtime_error("Tileset::getTileCollision() -> Invalid tile type provided.");
	return it->second;
}
