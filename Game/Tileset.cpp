/*
 * Tileset.cpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */

#include "Tileset.hpp"

#include <stdexcept>

#include "../Managers/AnimationManager.hpp"
#include "../main.hpp"
#include "../Math/Rectangle.hpp"

using std::range_error;
using std::runtime_error;
using std::string;

// The Null tile.
const Tile TILESET_NULLTILE;

TilesetData::TilesetData()
{
}

void TilesetData::setTileData(TileType type, uint l, uint m, uint u1, uint u2, uint u3)
{
	switch(type)
	{
		case TILE_WEST: _west.set(l, m, u1, u2, u3); break;
		case TILE_NORTH: _north.set(l, m, u1, u2, u3); break;
		case TILE_EAST: _east.set(l, m, u1, u2, u3); break;
		case TILE_SOUTH: _south.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_NORTHWEST: _corner_northwest.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_NORTHEAST: _corner_northeast.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_SOUTHEAST: _corner_southeast.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_SOUTHWEST: _corner_southwest.set(l, m, u1, u2, u3); break;
		case TILE_NORTHWEST: _northwest.set(l, m, u1, u2, u3); break;
		case TILE_NORTHEAST: _northeast.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHEAST: _southeast.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHWEST: _southwest.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_WEST: _corner_west.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_NORTH: _corner_north.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_EAST: _corner_east.set(l, m, u1, u2, u3); break;
		case TILE_CORNER_SOUTH: _corner_south.set(l, m, u1, u2, u3); break;
		case TILE_NORTHWEST_DOORLEFT: _northwest_doorleft.set(l, m, u1, u2, u3); break;
		case TILE_NORTHWEST_DOORRIGHT: _northwest_doorright.set(l, m, u1, u2, u3); break;
		case TILE_NORTHEAST_DOORLEFT: _northeast_doorleft.set(l, m, u1, u2, u3); break;
		case TILE_NORTHEAST_DOORRIGHT: _northeast_doorright.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHEAST_DOORLEFT: _southeast_doorleft.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHEAST_DOORRIGHT: _southeast_doorright.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHWEST_DOORLEFT: _southwest_doorleft.set(l, m, u1, u2, u3); break;
		case TILE_SOUTHWEST_DOORRIGHT: _southwest_doorright.set(l, m, u1, u2, u3); break;
		case TILE_FLOOR_A: _floor_a.set(l, m, u1, u2, u3); break;
		case TILE_FLOOR_B: _floor_b.set(l, m, u1, u2, u3); break;
		case TILE_FLOOR_C: _floor_c.set(l, m, u1, u2, u3); break;
		case TILE_FLOOR_D: _floor_d.set(l, m, u1, u2, u3); break;
		default: throw runtime_error("TilesetData::setTileData() -> Invalid type: " + toString(type));
	}
}

Tileset::Tileset(Surface* meta, const string& name, uint width, uint height) : mName(name),
                                                                               mWidth(width),
                                                                               mHeight(height)
{
    if(!meta)
    {
        throw runtime_error("Tileset::Tileset() -> No meta surface provided.");
    }

    // Ensure that the width and height are valid.
    if(mWidth < 1 || mHeight < 1)
    {
        throw range_error("Tileset::Tileset() -> Invalid width or height specified for tileset: w("
                          + toString(mWidth)
                          + "), h("
                          + toString(mHeight)
                          + ")");
    }

    // Break up the surface into separate surfaces for each tile.
    for(uint h = 0; h != meta->getHeight() / mHeight; ++h)
    {
    	for(uint w = 0; w != meta->getWidth() / mWidth; ++w)
    	{
			// Place each tile into a collection.
			mTiles.push_back(Tile(meta, Rectangle((w * mWidth), (h * mHeight), mWidth, mHeight)));
		}
    }
}

const Tile& Tileset::at(uint id) const
{
    // Get the requested tile.
    if(id >= mTiles.size())
    {
        throw range_error("Tileset::at() -> Cannot retrieve tile with id '" + toString(id) +
                          "'.  Tileset size is '" + toString(mTiles.size()) + "'");
    }

    // If the ID is zero, then return the null tile.
    if(id == 0)
    {
    	return TILESET_NULLTILE;
    }

    // Return the requested tile.
    return mTiles[id - 1];
}

const uint Tileset::getHeight() const
{
    return mHeight;
}

const string& Tileset::getName() const
{
    return mName;
}

const TileData& Tileset::getTileData(TileType type) const
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
		case TILE_FLOOR_A: return _floor_a;
		case TILE_FLOOR_B: return _floor_b;
		case TILE_FLOOR_C: return _floor_c;
		case TILE_FLOOR_D: return _floor_d;
		default: throw runtime_error("Tileset::getTileData() -> Invalid type provided: " + toString(type));
	}
}

const uint Tileset::getWidth() const
{
    return mWidth;
}
