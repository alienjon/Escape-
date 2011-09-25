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

#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Surface.hpp"
#include "../Game/TileData.hpp"
#include "../Game/TileLevel.hpp"
#include "TileType.hpp"

/**
 * @brief The tileset data holds all information needed to create a tileset.
 */
struct TilesetData
{
	/**
	 * @brief Default constructor.
	 */
	TilesetData()
	{}

	/**
	 * @brief Get the specified tile data.
	 * @param data The tile type to get.
	 * @return The requested tile data.
	 * @throws std::range_error if the tile does not exist.
	 */
	const TileData& get(TileType type) const;

	/**
	 * @brief Set the specified tile data.
	 * @param type The type of data to set.
	 * @param l The lower tile UID.
	 * @param m The middle tile UID.
	 * @param u1 The first-upper tile UID.
	 * @param u2 The second-upper tile UID.
	 * @param u3 The third-upper tile UID.
	 * @param quad The collision area of the tile.
	 */
	void setTileData(TileType type, unsigned int l, unsigned int m, unsigned int u1, unsigned int u2, unsigned int u3, const Quadrilateral& quad);

	// The name for the tileset.
	std::string name;

	// The name for the tileset's meta-image.
	std::string metaFilename;

	// The dimensions of a tile.
	unsigned int width;
	unsigned int height;

	// The data for each tile.
	TileData _west, _north, _east, _south, _corner_northwest, _corner_northeast, _corner_southwest, _corner_southeast,
			 _northwest, _northeast, _southwest, _southeast, _corner_west, _corner_north, _corner_east, _corner_south,
			 _northwest_doorleft, _northwest_doorright, _northeast_doorleft, _northeast_doorright, _southeast_doorleft,
			 _southeast_doorright, _southwest_doorleft, _southwest_doorright, _emptyfloor, _closeddoor_west, _closeddoor_east,
			 _opendoor_west, _opendoor_east;
};

/**
 * @brief A tileset maintains tile data and provides tiles for maps.
 */
class Tileset
{
    public:
    /**
     * @brief Construct a tileset based on specified data.
     * @param data The data used to create the tileset.
     * @note A tileset is considered the owner of it's individual tile images but NOT the meta images.  Don't clean up the meta image.
     */
    Tileset(const TilesetData& data);

    /**
     * @brief Gets the height of a single tile.
     * @return The height of a single tile.
     */
    inline const unsigned int getHeight() const
    {
    	return mHeight;
    }

    /**
     * @brief Get the name of this tileset.
     * @return The name of the tileset.
     */
    inline const std::string& getName() const
    {
    	return mName;
    }

    /**
     * @brief Get a tile by type and level.
     * @param type The type of tile to get.
     * @param level The level of the tile type to get.
     * @return The area on the tileset surface that represents the tile.
     */
    const Rectangle& getTile(TileType type, TileLevel level) const;

    /**
     * @brief Get a tile's collision area.
     * @param type The type of tile to get.
     * @return The collision area for the requested tile type.
     */
    const Quadrilateral& getTileCollision(TileType type) const;

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

    protected:
    /**
     * The tileset's meta image.
     */
    Surface* mSurface;

    /**
     * The name and dimensions of the tileset.
     */
    std::string mName;
    unsigned int mWidth, mHeight;

    /**
     * The tiles as defined by the area's they represent on the map.
     */
    std::map<TileType, Rectangle> mLowerTiles,
								  mMiddleTiles,
								  mUpper1Tiles,
								  mUpper2Tiles,
								  mUpper3Tiles;

    /**
     * The collision areas.
     */
    std::map<TileType, Quadrilateral> mCollisionAreas;
};

#endif /* TILESET_HPP_ */
