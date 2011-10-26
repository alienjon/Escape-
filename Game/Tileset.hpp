/*
 * Tileset.hpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */
#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <map>
#include <string>

#include "../Math/CollisionArea.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Surface.hpp"

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
     */
    Tileset(const std::string& filename);

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
	const Rectangle& getTile(Tileset::TileType type) const;

	/**
	 * @brief Get the collision area for the specified tile.
	 * @param tile The type of tile to get.
	 * @return The collision area for that tile.
	 * @note The collision area is relative to the tile itself.
	 */
	const CollisionArea& getTileCollision(Tileset::TileType type) const;

    /**
     * @brief Get the tileset's meta image.
     * @return The tileset's meta image.
     */
    inline const Surface* getTilesetSurface() const
	{
		return mSurface;
	}

    /**
     * @brief Gets the width of a single tile.
     * @return The width of a single tile.
     */
    inline const unsigned int getWidth() const
    {
    	return mWidth;
    }

    private:
    // The tileset's meta image.
    Surface* mSurface;

    // The name and dimensions of the tileset.
    unsigned int mWidth, mHeight;

    // The tiles as defined by the area's they represent on the map.
    std::map<Tileset::TileType, Rectangle> mTiles;
    std::map<Tileset::TileType, CollisionArea> mCollisions;
};

extern const std::string TILESET_DIRECTORY;

#endif /* TILESET_HPP_ */
