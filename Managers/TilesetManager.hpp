/*
 * TilesetManager.hpp
 *
 *  Created on: May 26, 2009
 *      Author: alienjon
 */

#ifndef TILESETMANAGER_HPP_
#define TILESETMANAGER_HPP_

#include <map>
#include <string>

#include "../Game/Tileset.hpp"

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
     * @brief Retrieve a tileset by a specified key.
     * @param key The identifying key for the tileset.
     * @return The requested tileset.
     */
    static const Tileset* get(const std::string& key);

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
     * The tileset file data extracted into a list of vectors.
     */
    std::list<TilesetData> mData;

    /**
     * The collection of tilesets.
     */
    std::map<std::string, Tileset*> mTilesets;
};

#endif /* TILESETMANAGER_HPP_ */
