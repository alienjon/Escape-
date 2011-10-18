/*
 * Map.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>

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
    Map(unsigned int width, unsigned int height, const Tileset* tileset);

    /**
     * @brief Check an area vs. map collisions (hitting a wall, for example)
     * @param area The area to check.
     * @return True if a collision occurred.
     */
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
     * @brief Draw the lower map (probably just the ground)
     * @param renderer The graphics object.
     * @param viewport The visible area on the screen.
     */
    virtual void drawLower(Renderer& renderer, const Viewport& viewport);

    /**
     * @brief Draw the middle map (objects on the ground, but still below the creatures)
     * @param renderer The graphics object.
     * @param viewport The visible area on the screen.
     * @param end_y The tile-y level to draw.
     */
    virtual void drawMiddle(Renderer& renderer, const Viewport& viewport, int end_y = -1);

    /**
     * @brief Draw the upper map (stuff above the creatures)
     * @param renderer The graphics object.
     * @param viewport The visible area on the screen.
     */
    virtual void drawUpper(Renderer& renderer, const Viewport& viewport);

    /**
     * @brief Get the complexity of the map.
     * @return The complexity of the map (cellsWidth * cellsHeight)
     */
    virtual unsigned int getComplexity() const;

    /**
     * @brief Get the location on the map that is the entrance for the player.
     * @return The entrance location.
     */
    const Vector& getEntrance() const;

    /**
     * @brief Get the exit area that the player must activate to go to the next level.
     * @return The exit area.
     */
    const Rectangle& getExit() const;

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

    protected:
    /**
     * The upper, middle and lower maps.
     */
    std::vector<std::pair<Point, Rectangle> > mLMap, mMMap, mU1Map, mU2Map, mU3Map;

    /**
     * The collision areas.
     */
    std::vector<Quadrilateral> mCollisionAreas;

    /**
     * The width and height of the map in tiles.
     */
    unsigned int mWidth, mHeight;

    /**
     * This map's tileset.
     */
    const Tileset* mTileset;

    /**
     * This is the entrance location.
     */
    Vector mEntranceLocation;

    /**
     * This is the exit area.
     */
    Rectangle mExitArea;

    private:
    /**
     * Draw a level.
     */
    void mDrawLevel(Renderer& renderer, const Viewport& viewport, std::vector<std::pair<Point, Rectangle> >& tiles, int end_y = -1);
};

extern const unsigned int MAP_CELL_SIDE;

#endif /* MAP_HPP_ */
