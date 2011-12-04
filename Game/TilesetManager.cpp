/*
 * TilesetManager.cpp
 *
 *  Created on: May 26, 2009
 *      Author: alienjon
 */
#include "TilesetManager.hpp"

#include <fstream>
#include <stdexcept>

#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::ifstream;
using std::list;
using std::runtime_error;
using std::string;
using std::vector;

TilesetManager::TilesetManager()
{
    // Open the tileset data file.
    ifstream file(FILE_TILESET_DATA, ifstream::in);

    // Check to make sure it was opened.
    if(!file.good())
        throw runtime_error("TilesetManager() -> Error opening tileset data file.");

    // Iterate through each line in the tileset data file.
    string line;
    for(unsigned int line_num = 1; getline(file, line); ++line_num)
    {
    	// If the line is empty or a comment, continue.
    	if(line.empty() || line[0] == '#')
    		continue;

        // Add the tileset filename.
        mData.push_back("Tilesets/" + line);
    }

    // Close the file.
    file.close();
}

TilesetManager::~TilesetManager()
{
}

void TilesetManager::create()
{
    if(!mManager)
        mManager = new TilesetManager();
}

unsigned int TilesetManager::determineSize()
{
    return (unsigned int)mManager->mData.size();
}

const string TilesetManager::getCurrentResourceName()
{
    // If we are currently debugging, just note that a tileset is loading.
	return "Tileset: " + *(mManager->mData.begin());
}

bool TilesetManager::loadResource()
{
    // If the data is empty, return false
    if(mManager->mData.empty())
        return false;

	// Add the first entry in the list as the new tileset.
	mManager->mTilesets.push_back(Tileset(*(mManager->mData.begin())));

    // Remove the first entry.
    mManager->mData.pop_front();

    // Return true if more resources need to be loaded.
    return (mManager->mData.empty()) ? false : true;
}

void TilesetManager::terminate()
{
    delete mManager;
    mManager = 0;
}

const Tileset& TilesetManager::getRandom()
{
    // Make sure the manager exists.
    if(!mManager)
        throw runtime_error("TilesetManager::get() -> TilesetManager has not yet been created.");

    // Get a random position between 0 (the first position) and size-1 (the last position)
    int pos = random<int>(0, mManager->mTilesets.size() - 1);

    // Return a random tileset.
    return mManager->mTilesets[pos];
}

TilesetManager* TilesetManager::mManager = 0;

const char* TilesetManager::FILE_TILESET_DATA = "tilesets.dat";
