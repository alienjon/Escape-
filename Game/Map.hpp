/*
 * Map.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>

#include "../Math/CollisionArea.hpp"
#include "../Math/Point.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../Game/Tileset.hpp"
#include "../Engine/Viewport.hpp"

/**
 * @brief A map is the visual representation of a level.
 */
class Map
{
    public:
    /**
     * @brief Randomly generate a map.
     * @param width The width of the map grid.
     * @param height The height of the map grid.
     * @param tileset The tileset for the map to use.
     */
	Map(unsigned int width, unsigned int height);

    /**
     * @brief Check an area vs. map collisions (hitting a wall, for example)
     * @param area The area to check.
     * @return True if a collision occurred.
     *///@todo remove quadrilaterals, just use rectangles
    virtual bool checkCollision(const Quadrilateral& area) const;

    /**
     * @brief Check an area vs. map collisions (hitting a wall, for example)
     * @param the area to check.
     * @return True if a collision occurred.
     */
    virtual bool checkCollision(const Rectangle& area) const;

    /**
     * @brief Make a copy of the map image.
     * @return A copy of the map image.
     */
    virtual Surface* copyMapImage() const;

    /**
     * @brief Draw the map.
     * @param renderer The graphics object.
     * @param viewport The visible area on the screen.
     */
    virtual void draw(Renderer& renderer, const Viewport& viewport);

    /**
     * @brief Get the complexity of the map.
     * @return The complexity of the map (cellsWidth * cellsHeight)
     */
    virtual unsigned int getComplexity() const;

    /**
     * @brief Get the location on the map that is the entrance/exit for the player.
     * @return The portal location.
     */
    const Vector& getPortal() const;

    /**
     * @brief Returns the pixel height of the map.
     * @return The height of the map.
     */
    virtual unsigned int getHeight() const;


    /**
     * @brief Get this map's tileset.
     * @return The map's tileset.
     */
    virtual const Tileset& getTileset() const;

    /**
     * @brief Returns the pixel width of the map.
     * @return The width of the map.
     */
    virtual unsigned int getWidth() const;

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
     * @brief Check if the area is in bounds.
     * @param area The area to see if it is within (collides with) the maps boundaries.
     * @return True if the area is outside or otherwise intersecting the edges of the map.
     */
    virtual bool isOutOfBounds(const Rectangle& area) const;

    private:

    // The walls and collisions.
    std::vector<std::pair<Point, Rectangle> > mMap;
    std::vector<CollisionArea> mCollisions;

    // The width and height of the map in tiles.
    unsigned int mWidth, mHeight;

    // This map's tileset.
    const Tileset* mTileset;

    // This is the entrance location.
    Vector mPortal;
};

extern const unsigned int MAP_CELL_SIDE;

#endif /* MAP_HPP_ */
