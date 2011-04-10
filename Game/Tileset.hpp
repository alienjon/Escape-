/*
 * Tileset.hpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */

#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <string>
#include <vector>

#include "../Entities/Non-Creatures/Tile.hpp"
#include "../Game/TileData.hpp"
#include "TileType.hpp"
#include "../Engine/Surface.hpp"

typedef std::vector<Tile> Tiles;

/**
 * @brief The tileset data holds all information needed to create a tileset.
 */
struct TilesetData
{
	/**
	 * @brief Default constructor.
	 */
	TilesetData();

	/**
	 * @brief Set the specified tile data.
	 * @param type The type of data to set.
	 * @param l The lower tile UID.
	 * @param m The middle tile UID.
	 * @param u1 The first-upper tile UID.
	 * @param u2 The second-upper tile UID.
	 * @param u3 The third-upper tile UID.
	 */
	void setTileData(TileType type, uint l, uint m, uint u1, uint u2, uint u3);

	std::string name;
	std::string metaFilename;
	uint width;
	uint height;
	// @todo clean this up?
	TileData _west, _north, _east, _south, _corner_northwest, _corner_northeast, _corner_southwest, _corner_southeast,
			 _northwest, _northeast, _southwest, _southeast, _corner_west, _corner_north, _corner_east, _corner_south,
			 _northwest_doorleft, _northwest_doorright, _northeast_doorleft, _northeast_doorright, _southeast_doorleft,
			 _southeast_doorright, _southwest_doorleft, _southwest_doorright, _floor_a, _floor_b, _floor_c, _floor_d;
};

/**
 * @brief A tileset is a collection of images used to display tiles on a map.
 *
 * A tileset loads from a meta surface and will generate tiles of a width and height
 * that, when multiplied together, equal the total area of the meta surface.
 */
class Tileset
{
	friend class TilesetManager;

    public:
    /**
     * @brief A tileset must be defined with a single tile's width and height as well as the image it uses to generate the tiles.
     * @param meta The meta surface.
     * @param name The name of the tileset.
     * @param width The width of a single tile in the meta image.
     * @param height The height of a single tile in the meta image.
     * @note A tileset is considered the owner of it's individual tile images but NOT the meta images.  Don't clean up the meta image.
     */
    Tileset(Surface* meta, const std::string& name, uint width, uint height);

    /**
     * @brief Retrieve the tile at the specifid ID.
     * @param id The id of the tile to retrieve.
     * @return The tile.
     */
    const Tile& at(uint id) const;

    /**
     * @brief Gets the height of a single tile.
     * @return The height of a single tile.
     */
    const uint getHeight() const;

    /**
     * @brief Get the name of this tileset.
     * @return The name of the tileset.
     */
    const std::string& getName() const;

    /**
     * @brief Get this tilesets tiledata based on the provided tile type.
     * @param type The type of tile to get.
     * @return The tile data.
     */
    const TileData& getTileData(TileType type) const;

    /**
     * @brief Gets the width of a single tile.
     * @return The width of a single tile.
     */
    const uint getWidth() const;

    protected:
    /**
     * The collection of tiles.
     */
    Tiles mTiles;

    /**
     * The tileset's name.
     */
    std::string mName;

    /**
     * The dimension of a single tile in this tileset.
     */
    const uint mWidth;
    const uint mHeight;

    private:
	TileData _west, _north, _east, _south, _corner_northwest, _corner_northeast, _corner_southwest, _corner_southeast,
			 _northwest, _northeast, _southwest, _southeast, _corner_west, _corner_north, _corner_east, _corner_south,
			 _northwest_doorleft, _northwest_doorright, _northeast_doorleft, _northeast_doorright, _southeast_doorleft,
			 _southeast_doorright, _southwest_doorleft, _southwest_doorright, _floor_a, _floor_b, _floor_c, _floor_d;
};

#endif /* TILESET_HPP_ */
