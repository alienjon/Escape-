/*
 * TilesetManager.cpp
 *
 *  Created on: May 26, 2009
 *      Author: alienjon
 */
#include "TilesetManager.hpp"

#include <stdexcept>
#include <vector>

#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::ifstream;
using std::list;
using std::map;
using std::runtime_error;
using std::string;
using std::vector;

TilesetManager::TilesetManager()
{
    // Open the tileset data file.
    ifstream file(FILE_TILESET_DATA, ifstream::in);

    // Check to make sure it was opened.
    if(!file.good())
    {
        // Problem opening the file.
        throw runtime_error("TilesetManager() -> Error opening tileset data file.");
    }

    // Iterate through each line in the tileset data file.
    string line;
    for(unsigned int line_num = 1; getline(file, line); ++line_num)
    {
    	// If the line is empty or a comment, continue.
    	if(line.empty() || line[0] == '#')
    		continue;

        // Add the tileset filename.
        mData.push_back(line);
    }

    // Close the file.
    file.close();
}

TilesetManager::~TilesetManager()
{
	// Delete all the tilesets.
	for(vector<Tileset*>::iterator it = mTilesets.begin(); it != mTilesets.end(); ++it)
		delete *it;
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
	return (Game::isDebug()) ? ("Tileset: " + *(mManager->mData.begin())) : "Unknown Tileset";
}

bool TilesetManager::loadResource()
{
    // If the data is empty, return false
    if(mManager->mData.empty())
        return false;

	// Add the first entry in the list as the new tileset.
	mManager->mTilesets.push_back(new Tileset(*(mManager->mData.begin())));

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

const Tileset* TilesetManager::getRandom()
{
    // Make sure the manager exists.
    if(!mManager)
        throw runtime_error("TilesetManager::get() -> TilesetManager has not yet been created.");

    // Get a random position between 0 (the first position) and size-1 (the last position)
    size_t pos = random(0, (int)mManager->mTilesets.size() - 1);

    // Return a random tileset.
    return mManager->mTilesets[pos];
}

TilesetManager* TilesetManager::mManager = 0;

const char* TilesetManager::FILE_TILESET_DATA = "tilesets.dat";
