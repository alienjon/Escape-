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

using std::range_error;
using std::runtime_error;
using std::string;

const TileData& TilesetData::get(TileType type) const
{
	switch(type)
	{
		case TILE_WEST: return _west;
		case TILE_NORTH: return _north;
		case TILE_EAST: return _east;
		case TILE_SOUTH: return _south;
		case TILE_CORNER_NORTHWEST: return _corner_northwest;
		case TILE_CORNER_NORTHEAST: return _corner_northeast;
		case TILE_CORNER_SOUTHEAST: return _corner_southeast;
		case TILE_CORNER_SOUTHWEST: return _corner_southwest;
		case TILE_NORTHWEST: return _northwest;
		case TILE_NORTHEAST: return _northeast;
		case TILE_SOUTHEAST: return _southeast;
		case TILE_SOUTHWEST: return _southwest;
		case TILE_CORNER_WEST: return _corner_west;
		case TILE_CORNER_NORTH: return _corner_north;
		case TILE_CORNER_EAST: return _corner_east;
		case TILE_CORNER_SOUTH: return _corner_south;
		case TILE_NORTHWEST_DOORLEFT: return _northwest_doorleft;
		case TILE_NORTHWEST_DOORRIGHT: return _northwest_doorright;
		case TILE_NORTHEAST_DOORLEFT: return _northeast_doorleft;
		case TILE_NORTHEAST_DOORRIGHT: return _northeast_doorright;
		case TILE_SOUTHEAST_DOORLEFT: return _southeast_doorleft;
		case TILE_SOUTHEAST_DOORRIGHT: return _southeast_doorright;
		case TILE_SOUTHWEST_DOORLEFT: return _southwest_doorleft;
		case TILE_SOUTHWEST_DOORRIGHT: return _southwest_doorright;
		case TILE_CLOSEDDOOR_WEST: return _closeddoor_west;
		case TILE_CLOSEDDOOR_EAST: return _closeddoor_east;
		case TILE_OPENDOOR_WEST: return _opendoor_west;
		case TILE_OPENDOOR_EAST: return _opendoor_east;
		case TILE_EMPTYFLOOR: return _emptyfloor;
		default: throw range_error("Tileset::getTile() -> Invalid type provided: " + toString(type));
	}
}

void TilesetData::setTileData(TileType type, unsigned int l, unsigned int m, unsigned int u1, unsigned int u2, unsigned int u3, const Quadrilateral& quad)
{
	switch(type)
	{
		case TILE_WEST: _west.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTH: _north.set(l, m, u1, u2, u3, quad); break;
		case TILE_EAST: _east.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTH: _south.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_NORTHWEST: _corner_northwest.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_NORTHEAST: _corner_northeast.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_SOUTHEAST: _corner_southeast.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_SOUTHWEST: _corner_southwest.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHWEST: _northwest.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHEAST: _northeast.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHEAST: _southeast.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHWEST: _southwest.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_WEST: _corner_west.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_NORTH: _corner_north.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_EAST: _corner_east.set(l, m, u1, u2, u3, quad); break;
		case TILE_CORNER_SOUTH: _corner_south.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHWEST_DOORLEFT: _northwest_doorleft.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHWEST_DOORRIGHT: _northwest_doorright.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHEAST_DOORLEFT: _northeast_doorleft.set(l, m, u1, u2, u3, quad); break;
		case TILE_NORTHEAST_DOORRIGHT: _northeast_doorright.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHEAST_DOORLEFT: _southeast_doorleft.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHEAST_DOORRIGHT: _southeast_doorright.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHWEST_DOORLEFT: _southwest_doorleft.set(l, m, u1, u2, u3, quad); break;
		case TILE_SOUTHWEST_DOORRIGHT: _southwest_doorright.set(l, m, u1, u2, u3, quad); break;
		case TILE_CLOSEDDOOR_WEST: _closeddoor_west.set(l, m, u1, u2, u3, quad); break;
		case TILE_CLOSEDDOOR_EAST: _closeddoor_east.set(l, m, u1, u2, u3, quad); break;
		case TILE_OPENDOOR_WEST: _opendoor_west.set(l, m, u1, u2, u3, quad); break;
		case TILE_OPENDOOR_EAST: _opendoor_east.set(l, m, u1, u2, u3, quad); break;
		case TILE_EMPTYFLOOR: _emptyfloor.set(l, m, u1, u2, u3, quad); break;
		default: throw range_error("TilesetData::setTileData() -> Invalid type: " + toString(type));
	}
}

Tileset::Tileset(const TilesetData& data) :
	mSurface(VideoManager::loadSurface(data.metaFilename)),
	mName(data.name),
	mWidth(data.width),
	mHeight(data.height)
{
    // Ensure that the width and height are valid.
    if(mWidth < 1 || mHeight < 1)
    {
        throw range_error("Tileset::Tileset() -> Invalid width or height specified for tileset: w("
                          + toString(mWidth) + "), h(" + toString(mHeight) + ")");
    }

    // For each type of tile calculate and store the various levels and the collision area.
    int tile_width = mSurface->getWidth() / mWidth;
    for(int i = TILE_NULL + 1; i != TILE_NPOS; ++i)
    {
    	if(data.get((TileType)i).l < 1)
    		throw runtime_error("Tileset::Tileset() -> The lower level of all tiles must be specified.");
    	mLowerTiles[(TileType)i] = Rectangle(((data.get((TileType)i).l - 1) % tile_width) * mWidth, ((data.get((TileType)i).l - 1)/ tile_width) * mHeight, mWidth, mHeight);

    	if(data.get((TileType)i).m > 0)
    		mMiddleTiles[(TileType)i] = Rectangle(((data.get((TileType)i).m  - 1) % tile_width) * mWidth, ((data.get((TileType)i).m - 1) / tile_width) * mHeight, mWidth, mHeight);
    	else
    		mMiddleTiles[(TileType)i] = Rectangle(0, 0, 0, 0);

    	if(data.get((TileType)i).u1 > 0)
    		mUpper1Tiles[(TileType)i] = Rectangle(((data.get((TileType)i).u1 - 1) % tile_width) * mWidth, ((data.get((TileType)i).u1 - 1) / tile_width) * mHeight, mWidth, mHeight);
    	else
    		mUpper1Tiles[(TileType)i] = Rectangle(0, 0, 0, 0);

    	if(data.get((TileType)i).u2 > 0)
    		mUpper2Tiles[(TileType)i] = Rectangle(((data.get((TileType)i).u2 - 1) % tile_width) * mWidth, ((data.get((TileType)i).u2 - 1) / tile_width) * mHeight, mWidth, mHeight);
    	else
    		mUpper2Tiles[(TileType)i] = Rectangle(0, 0, 0, 0);

    	if(data.get((TileType)i).u3 > 0)
    		mUpper3Tiles[(TileType)i] = Rectangle(((data.get((TileType)i).u3 - 1) % tile_width) * mWidth, ((data.get((TileType)i).u3 - 1) / tile_width) * mHeight, mWidth, mHeight);
    	else
    		mUpper3Tiles[(TileType)i] = Rectangle(0, 0, 0, 0);

    	mCollisionAreas[(TileType)i] = data.get((TileType)i).collision;
    }

}

const Quadrilateral& Tileset::getTileCollision(TileType type) const
{
	// Get the tile collision area for the requested level.
	return mCollisionAreas.find(type)->second;
}

const Rectangle& Tileset::getTile(TileType type, TileLevel level) const
{
	// Get the tile id for the requested level.
	switch(level)
	{
		case TILELEVEL_LOWER:
		{
			return mLowerTiles.find(type)->second;
		}
		case TILELEVEL_MIDDLE:
		{
			return mMiddleTiles.find(type)->second;
		}
		case TILELEVEL_UPPER1:
		{
			return mUpper1Tiles.find(type)->second;
		}
		case TILELEVEL_UPPER2:
		{
			return mUpper2Tiles.find(type)->second;
		}
		case TILELEVEL_UPPER3:
		{
			return mUpper3Tiles.find(type)->second;
		}
		default:
		{
			throw runtime_error("Tileset::getTile() -> Invalid tile level request.");
		}
	}
}
