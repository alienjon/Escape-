/*
 * TilesetManager.hpp
 *
 *  Created on: May 26, 2009
 *      Author: alienjon
 */
#ifndef TILESETMANAGER_HPP_
#define TILESETMANAGER_HPP_

#include <list>
#include <string>
#include <vector>

#include "../Game/Tileset.hpp"

/**
 * @brief Data needed to create a tileset.
 */
struct TilesetData
{
	/**
	 * @brief Constructor for information to build a tileset.
	 * @param fname The filename of the meta file to create the tileset.
	 * @param w The width of a single tile.
	 * @param h The height of a single tile.
	 */
	TilesetData(const std::string& fname, unsigned int w, unsigned int h);

	// The filename for the tileset's image.
	std::string filename;

	// The size of a single tile.
	unsigned int width, height;
};

/**
 * @brief A class to manage all tilesets.
 */
class TilesetManager
{
    public:
	virtual ~TilesetManager();

    /**
     * @brief Create the tileset manager.
     */
    static void create();

    /**
     * @brief Determine the number of animations this manager will manage.
     * @return The number of resources this manager manages.
     */
    static unsigned int determineSize();

    /**
     * @brief Get the name of the current resource.
     * @return The name of the next resource that will be loaded.
     */
    static const std::string getCurrentResourceName();

    /**
     * @brief Load the next resource.
     * @return True if the resource was successfully loaded, false if the last resource was loaded.
     */
    static bool loadResource();

    /**
     * @brief Delete the tileset manager.
     */
    static void terminate();

	/**
	 * @brief Retrieve a random tileset.
	 * @return A tileset.
	 */
	static const Tileset& getRandom();

    private:
    /**
     * The tileset manager.
     */
    static TilesetManager* mManager;

    /**
     * The tileset data file.
     */
    static const char* FILE_TILESET_DATA;

    /**
     * @brief Object to load, store and terminate all tilesets.
     */
    TilesetManager();

    /**
     * The tileset file data extracted into a list.
     */
    std::list<TilesetData> mData;

    /**
     * The collection of tilesets.
     */
    std::vector<Tileset> mTilesets;
};

#endif /* TILESETMANAGER_HPP_ */
