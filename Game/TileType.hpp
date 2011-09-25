/*
 * TileType.hpp
 *
 *  Created on: Sep 5, 2009
 *      Author: alienjon
 */
#ifndef TILETYPE_HPP_
#define TILETYPE_HPP_

#include <string>

// The string representations of the tile types.
extern const std::string TILETYPE_EMPTYFLOOR;
extern const std::string TILETYPE_WEST;
extern const std::string TILETYPE_NORTH;
extern const std::string TILETYPE_EAST;
extern const std::string TILETYPE_SOUTH;
extern const std::string TILETYPE_CORNER_NORTHWEST;
extern const std::string TILETYPE_CORNER_NORTHEAST;
extern const std::string TILETYPE_CORNER_SOUTHEAST;
extern const std::string TILETYPE_CORNER_SOUTHWEST;
extern const std::string TILETYPE_NORTHWEST;
extern const std::string TILETYPE_NORTHEAST;
extern const std::string TILETYPE_SOUTHEAST;
extern const std::string TILETYPE_SOUTHWEST;
extern const std::string TILETYPE_CORNER_WEST;
extern const std::string TILETYPE_CORNER_NORTH;
extern const std::string TILETYPE_CORNER_EAST;
extern const std::string TILETYPE_CORNER_SOUTH;
extern const std::string TILETYPE_NORTHWEST_DOORLEFT;
extern const std::string TILETYPE_NORTHWEST_DOORRIGHT;
extern const std::string TILETYPE_NORTHEAST_DOORLEFT;
extern const std::string TILETYPE_NORTHEAST_DOORRIGHT;
extern const std::string TILETYPE_SOUTHEAST_DOORLEFT;
extern const std::string TILETYPE_SOUTHEAST_DOORRIGHT;
extern const std::string TILETYPE_SOUTHWEST_DOORLEFT;
extern const std::string TILETYPE_SOUTHWEST_DOORRIGHT;
extern const std::string TILETYPE_CLOSEDDOOR_WEST;
extern const std::string TILETYPE_CLOSEDDOOR_EAST;
extern const std::string TILETYPE_OPENDOOR_WEST;
extern const std::string TILETYPE_OPENDOOR_EAST;
extern const std::string TILETYPE_NULL;
extern const std::string TILETYPE_NPOS;

/**
 * @brief These are the different types of wall tiles.
 */
typedef enum
{
    TILE_NULL                = 0,
    TILE_WEST                = 1,
    TILE_NORTH               = 2,
    TILE_EAST                = 3,
    TILE_SOUTH               = 4,
    TILE_CORNER_NORTHWEST    = 5,
    TILE_CORNER_NORTHEAST    = 6,
    TILE_CORNER_SOUTHEAST    = 7,
    TILE_CORNER_SOUTHWEST    = 8,
    TILE_NORTHWEST           = 9,
    TILE_NORTHEAST           = 10,
    TILE_SOUTHEAST           = 11,
    TILE_SOUTHWEST           = 12,
    TILE_CORNER_WEST         = 13,
    TILE_CORNER_NORTH        = 14,
    TILE_CORNER_EAST         = 15,
    TILE_CORNER_SOUTH        = 16,
    TILE_NORTHWEST_DOORLEFT  = 17,
    TILE_NORTHWEST_DOORRIGHT = 18,
    TILE_NORTHEAST_DOORLEFT  = 19,
    TILE_NORTHEAST_DOORRIGHT = 20,
    TILE_SOUTHEAST_DOORLEFT  = 21,
    TILE_SOUTHEAST_DOORRIGHT = 22,
    TILE_SOUTHWEST_DOORLEFT  = 23,
    TILE_SOUTHWEST_DOORRIGHT = 24,
    TILE_EMPTYFLOOR			 = 25,
    TILE_CLOSEDDOOR_WEST	 = 26,
    TILE_CLOSEDDOOR_EAST	 = 27,
    TILE_OPENDOOR_WEST		 = 28,
    TILE_OPENDOOR_EAST		 = 29,
    TILE_NPOS // Don't give this a value, it represents the end of the enumeration.
} TileType;

/**
 * @brief Convert the string to a tiletype.
 * @param type The string representation of the tiletype.
 * @return The tiletype.
 */
TileType toTileType(const std::string& type);

/**
 * @brief Convert the tiletype to its string representation.
 * @param type The tiletype.
 * @return The string representation of the tiletype.
 */
const std::string& toTileType(TileType type);

#endif /* TILETYPE_HPP_ */
