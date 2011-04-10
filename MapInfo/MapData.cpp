 /*
 * MapData.cpp
 *
 *  Created on: Jun 17, 2009
 *      Author: alienjon
 */

#include "MapData.hpp"

#include "Map.hpp"

typedef unsigned int uint;

bool isWall(TileType t)
{
    return (t >= 1) && (t <= 24);
}

MapData::MapData(uint width, uint height, TileType baseTile) : mWidth(width), mHeight(height)
{
    for(uint i = 0; i != mWidth * mHeight; ++i)
    {
        data.push_back(baseTile);
    }
}

void MapData::set(uint x, uint y, TileType t)
{
    if(((y * mWidth) + x) < (mWidth * mHeight))
    {
        data[(y * mWidth) + x] = t;
    }
}

bool MapData::isAreaClear(uint x, uint y, const MapRule& rule)
{
    // Make sure that X and Y stay in the bounds of the map.
    uint minX = ((x - rule.room_buffer) < 0) ? 0 : x - rule.room_buffer,
         maxX = ((x + rule.room_buffer) > rule.map_width - 1) ? rule.map_width - 1 : x + rule.room_buffer,
         minY = ((y - rule.room_buffer) < 0) ? 0 : y - rule.room_buffer,
         maxY = ((y + rule.room_buffer) > rule.map_height - 1) ? rule.map_height - 1 : y + rule.room_buffer;

    // Look at the points in the area denoted by minX -> maxX, minY -> maxY and see if a non
    // default tile is found.
    for(uint _yPos = minY; _yPos != maxY; ++_yPos)
    {
        for(uint _xPos = minX; _xPos != maxX; ++_xPos)
        {
            // If there is an intersection, return false.
            //@todo Need to implement indoor maps.
            if(((rule.outdoors) ? (data[(_yPos * mWidth) + _xPos] < TILE_NULL) : false))//(data[(_yPos * mWidth) + _xPos] != 'W')))
            {
                // Non default-tile detected.
                return false;
            }
        }
    }

    // All tiles are detected as default.
    return true;
}
