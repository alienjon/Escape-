/*
 * Map.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <string>

#include "MapData.hpp"
#include "MapRule.hpp"

#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../Entities/Non-Creatures/Tile.hpp"
#include "../Game/Tileset.hpp"

class Entity;

/**
 * @brief A map is the visual representation of a level.
 */
class Map
{
	// The environment data must have access to the private members of the map.
	friend class EnvironmentData;

    public:
    /**
     * @brief Load a map with the provided data.
     * @param data The data from which to load the map.
     *
     * @todo Remove this and replace it with the one below once I can get my hands on the Tiled code again...
     */
//    Map(const std::string& data);

    /**
     * @brief Load a map with the provided filename.
     * @param mapFile The map file to open.
     */
    Map(const std::string& mapFile);

    /**
     * @brief Create a random map using the provided map rule.
     * @param rules The rules to follow in order to create the map.
     */
    Map(const MapRule& rule);

    /**
     * @brief Draw the lower map (probably just the ground)
     * @param renderer The graphics object.
     */
    virtual void drawLower(Renderer& renderer);

    /**
     * @brief Draw the middle map (objects on the ground, but still below the creatures)
     * @param renderer The graphics object.
     */
    virtual void drawMiddle(Renderer& renderer);

    /**
     * @brief Draw the upper map (stuff above the creatures)
     * @param renderer The graphics object.
     */
    virtual void drawUpper(Renderer& renderer);

    /**
     * @brief Extract the map's state as a data string.
     * @return The current map's state as a saved base64 data string.
     */
    virtual std::string extract() const;

    /**
     * @brief Returns the number of tiles in this map's width.
     * @return The width of the map.
     */
    virtual int getWidth() const;

    /**
     * @brief Returns the number of tiles in this map's height.
     * @return The height of the map.
     */
    virtual int getHeight() const;

    /**
     * @brief Checks if an area is on the map.
     * @param x The x position.
     * @param y The y position.
     * @param width The width.
     * @param height The height.
     * @return True if the area is completely on the map.
     */
    virtual bool isOnMap(int x, int y, int width, int height) const;

    /**
     * @brief Check if a entity is in bounds.
     * @param entity The entity to check.
     * @return True if the entity is outside or otherwise intersecting the edges of the map.
     */
    virtual bool isOutOfBounds(const Entity& entity) const;

    /**
     * @brief Check if the area is in bounds.
     * @param area The area to see if it is within (collides with) the maps boundaries.
     * @return True if the area is outside or otherwise intersecting the edges of the map.
     */
    virtual bool isOutOfBounds(const Rectangle& area) const;

    protected:
    /**
     * The upper, middle and lower maps.
     */
    typedef std::vector<Tile> MapLayer; // @todo or Tile*?
    MapLayer mLMap;
    MapLayer mMMap;
    MapLayer mU1Map;
    MapLayer mU2Map;
    MapLayer mU3Map;

    /**
     * The width and height of the map.
     */
    uint mWidth;
    uint mHeight;

    /**
     * This map's tileset.
     */
    const Tileset* mTileset;
};

#endif /* MAP_HPP_ */
