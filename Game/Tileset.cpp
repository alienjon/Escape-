/*
 * Tileset.cpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */
#include "Tileset.hpp"

#include <stdexcept>

#include "../main.hpp"
#include "../Managers/VideoManager.hpp"

using std::map;
using std::runtime_error;
using std::string;

Tileset::Tileset(const string& filename) :
	mSurface(VideoManager::loadSurface(TILESET_DIRECTORY + filename))
{
	// Calculate the width and height.
	mWidth  = mSurface->getWidth()  / 3;
	mHeight = mSurface->getHeight() / 3;

	// Create the map areas.
	mTiles[NORTHWEST] = Rectangle(0, 0, mWidth, mHeight);
	mTiles[NORTH]	  = Rectangle(mWidth, mHeight * 2, mWidth, mHeight);
	mTiles[NORTHEAST] = Rectangle(mWidth * 2, 0, mWidth, mHeight);
	mTiles[WEST]	  = Rectangle(0, mHeight, mWidth, mHeight);
	mTiles[EAST]	  = Rectangle(mWidth * 2, mHeight, mWidth, mHeight);
	mTiles[SOUTHWEST] = Rectangle(0, mHeight * 2, mWidth, mHeight);
	mTiles[SOUTH]	  = Rectangle(mWidth, 0, mWidth, mHeight);
	mTiles[SOUTHEAST] = Rectangle(mWidth * 2, mHeight * 2, mWidth, mHeight);
	mTiles[EMPTYFLOOR]= Rectangle(0, 0, 0, 0);

	/* Create the collision areas based on the width of the collision area. */
	int col_size = 8; // @todo Should this be fixed or set with the tileset?
	// The empty floor.
	CollisionArea area;
	mCollisions[EMPTYFLOOR]= area;

	// The north wall.
	area = CollisionArea();
	area.addRectangle(Rectangle(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[NORTH] = area;

	// The south wall.
	area = CollisionArea();
	area.addRectangle(Rectangle(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[SOUTH] = area;

	// The west wall.
	area = CollisionArea();
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[WEST] = area;

	// The east wall.
	area = CollisionArea();
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[EAST] = area;

	// The northwest wall.
	area = CollisionArea();
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHWEST] = area;

	// The northeast wall.
	area = CollisionArea();
	area.addRectangle(Rectangle(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHEAST] = area;

	// The southeast wall.
	area = CollisionArea();
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.addRectangle(Rectangle(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHEAST] = area;

	// The southwest wall.
	area = CollisionArea();
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.addRectangle(Rectangle((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHWEST] = area;
}

const Rectangle& Tileset::getTile(Tileset::TileType type) const
{
	map<Tileset::TileType, Rectangle>::const_iterator it = mTiles.find(type);
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

const string TILESET_DIRECTORY = "Tilesets/";
