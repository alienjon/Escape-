/*
 * Tileset.hpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */
#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../Game/CollisionArea.hpp"

/**
 * @brief A tileset maintains tile data and provides tiles for maps.
 */
class Tileset
{
    public:
	enum TileType
	{
		NORTHWEST,
		NORTH,
		NORTHEAST,
		WEST,
		EAST,
		SOUTHWEST,
		SOUTH,
		SOUTHEAST,
		EMPTYFLOOR
	};

    /**
     * @brief Construct a tileset.
     * @param filename The filename of the tileset.
     * @param width The width of a single tile.
     * @param height The height of a single tile.
     */
    Tileset(const std::string& filename, unsigned int width, unsigned int height);

    /**
     * @brief Gets the height of a single tile.
     * @return The height of a single tile.
     */
    inline const unsigned int getHeight() const
    {
    	return mHeight;
    }

	/**
	 * @brief Get a tile by type and level.
	 * @param type The type of tile to get.
	 * @param level The level of the tile type to get.
	 * @return The area on the tileset surface that represents the tile.
	 */
	const sf::Image& getTile(Tileset::TileType type) const;

	/**
	 * @brief Get the collision area for the specified tile.
	 * @param tile The type of tile to get.
	 * @return The collision area for that tile.
	 * @note The collision area is relative to the tile itself.
	 */
	const CollisionArea& getTileCollision(Tileset::TileType type) const;

    /**
     * @brief Gets the width of a single tile.
     * @return The width of a single tile.
     */
    inline const unsigned int getWidth() const
    {
    	return mWidth;
    }

    private:
    // The name and dimensions of the tileset.
    unsigned int mWidth, mHeight;

    // The tiles as defined by the area's they represent on the map.
    std::map<Tileset::TileType, sf::Image> mTiles;
    std::map<Tileset::TileType, CollisionArea> mCollisions;
};

#endif /* TILESET_HPP_ */
