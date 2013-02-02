/*
 * Map.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Game/CollisionArea.hpp"
#include "../Game/Tileset.hpp"

/**
 * @brief A map is the visual representation of a level.
 */
class Map : public sf::Drawable
{
    public:
    /**
     * @brief Randomly generate a map.
     * @param width The width of the map grid in cells.
     * @param height The height of the map grid in cells.
     * @param tileset The tileset for the map to use.
     */
	Map(unsigned int width, unsigned int height);
	virtual ~Map()
	{}

    /**
     * @brief Check an area vs. map collisions (ie: hitting a wall)
     * @param the area to check.
     * @return True if a collision occurred.
     */
    virtual bool checkCollision(const sf::FloatRect& area) const;

    /**
     * @brief Draw the map.
     * @param target The render target.
     * @param states The render states.
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * @brief Get the height of the map in cells (as opposed to tiles or pixels).
     * @return The number of cells in the map's height.
     */
    inline unsigned int getCellHeight() const
    {
    	return mHeight;
    }

    /**
     * @brief Get the width of the map in cells (as opposed to tiles or pixels).
     * @return The number of cells in the map's width.
     */
    inline unsigned int getCellWidth() const
    {
    	return mWidth;
    }

    /**
     * @brief Get the complexity of the map.
     * @return The complexity of the map (cellsWidth * cellsHeight)
     */
    virtual unsigned int getComplexity() const;

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

    private:
    // The walls and collisions.@todo remove?
//    std::vector<std::pair<sf::Sprite, CollisionArea> > mMap;

    // The visual map.
    sf::Texture mMapTexture;
    sf::Sprite mMapSprite;

    // This vertex array holds collections of 4 vertices that define individual tiles for the map to draw.
    sf::VertexArray mTiles;

    // The collision areas.
    std::vector<CollisionArea> mCollisions;

    // The width and height of the map in tiles.
    unsigned int mWidth, mHeight;

    // This map's tileset.
    const Tileset& mTileset;
};

extern const unsigned int MAP_CELL_SIDE;

#endif /* MAP_HPP_ */
