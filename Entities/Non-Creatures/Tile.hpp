/*
 * Tile.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */

#ifndef TILE_HPP_
#define TILE_HPP_

#include "../../Entities/Entity.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Engine/Renderer.hpp"
#include "../../Engine/Surface.hpp"

/**
 * @brief A single image within the map.  It is related to an entity.
 */
class Tile : public Entity
{
    public:
	/**
	 * @brief A null tile with no display and no dimension.
	 */
	Tile();

    /**
     * @brief A tile is a sprite specifically used for maps.
     * @param meta The meta surface from which the tile is displayed.
     * @param area The area of the surface to draw.
     */
    Tile(Surface* meta, const Rectangle& area);

    /**
     * @brief Draw the tile.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    protected:
    /**
     * The tile's surface.
     */
    Surface* mSurface;
};

#endif /* TILE_HPP_ */
