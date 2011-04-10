/*
 * MapData.hpp
 *
 *  Created on: Jun 17, 2009
 *      Author: alienjon
 */

#ifndef MAPDATA_HPP_
#define MAPDATA_HPP_

#include <vector>

#include "../MapInfo/Map.hpp"
#include "../Game/TileType.hpp"

class MapRule;

/**
 * @brief Checks if the provided character matches a regular wall tile.
 * @param t The tile to check.
 * @return True if the provided tile is a wall tile.
 */
bool isWall(TileType t);

/**
 * @brief Contains information pertinent for map creation.
 */
class MapData
{
	friend class Map;
    public:
    /**
     * @brief A MapData object acts as a means to store tile data as a map is being generated.
     * @param width The width of the map.
     * @param height The height of the map.
     * @param baseTile The base tile to fill the map with.
     */
    MapData(unsigned int width, unsigned int height, TileType baseTile = TILE_NULL);

    /**
     * @brief Set the provided wall tile to the provided position.
     * @param x The x position of the tile.
     * @param y The y position of the tile.
     * @param t The tile to place.
     */
    void set(unsigned int x, unsigned int y, TileType t);

    /**
     * @brief Checks if the provided position is clear of map tiles in a range indicated by the map rule.
     * @param x The x position.
     * @param y The y position.
     * @param rule The map rule that details both whether this is an indoor/outdoor map and the buffer between walls.
     */
    bool isAreaClear(unsigned int x, unsigned int y, const MapRule& rule);

    private:
    unsigned int mWidth, mHeight;
    std::vector<TileType> data;
};

#endif /* MAPDATA_HPP_ */
