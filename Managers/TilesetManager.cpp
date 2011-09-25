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
    string line, tileset_name;
    TilesetData data;
    for(unsigned int line_num = 1; getline(file, line); ++line_num)
    {
    	// If the line is a comment, then continue.
    	if(line.empty() || line[0] == '#')
    	{
    		continue;
    	}
    	// If the next line begins with a '<', it should be a tileset definition.
    	else if(line.find_first_of('<') < (line.size() - 1))
    	{
    		// If the last character isn't a close-carrot, then this is an invalid definition.
    		if(line.find_first_of('>') != (line.size() - 1))
    		{
    			throw runtime_error(FILE_TILESET_DATA + string(": ") + toString(line_num) +
									string(": '") + line + string("' is an invalid tileset definition."));
    		}
    		else
    		{
        		// If this is not the first entry, then add the previous one to the collection.
        		if(!mData.empty())
        		{
        			mData.push_back(data);
        		}

        		// Create and configure a new tileset data.
        		data = TilesetData();
        		string::size_type pos = line.find_first_of('<') + 1 ; // Skip the '<'.
        		data.name  		  = extractDataLine(line, pos, ':');
        		data.metaFilename = extractDataLine(line, pos, ':');
        		data.width 		  = toInt(extractDataLine(line, pos, ':'));
        		data.height 	  = toInt(extractDataLine(line, pos, '>')); // Look for the end carrot.
    		}
    	}
    	// Continue adding to the definition.
    	else
    	{
    		// Find the first non-space and then grab the lower (l), middle (m), first, second and third upper
    		//	(u1, u2, u3) UIDs.  Then add them to the data set.
    		string::size_type pos = line.find_first_not_of(" \t\n");
    		string _type = extractDataLine(line, pos, ':');
    		TileType type = toTileType(_type);

    		// Check the type.
    		if(type == 0)
    		{
    			Logger::log("Warning: '" + _type + "' is not a valid tile type.");
    		}
    		uint l  = toInt(extractDataLine(line, pos, ':'));

    		// Check the lower layer.
    		if(l == 0)
    		{
    			Logger::log("Warning: '" + data.name + "' has a null tile set for it's lower level.");
    		}
    		else if(pos == line.size())
    		{
    			Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
    		}
    		uint m  = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		uint u1 = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		uint u2 = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		uint u3 = toInt(extractDataLine(line, pos, ':'));
    		Vector p1, p2, p3, p4;
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p1.x = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p1.y = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p2.x = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p2.y = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p3.x = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p3.y = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p4.x = toInt(extractDataLine(line, pos, ':'));
    		if(pos == line.size())
			{
				Logger::log("Warning: Problem parsing line " + toString(line_num) + " in " + FILE_TILESET_DATA + ": not enough layers specified.");
			}
    		p4.y = toInt(extractDataLine(line, pos, ':'));

    		data.setTileData(type, l, m, u1, u2, u3, Quadrilateral(p1, p2, p3, p4));
    	}
    }

    // Add the last tileset data.
    mData.push_back(data);

    // Close the file.
    file.close();
}

TilesetManager::~TilesetManager()
{
	// Delete all the tilesets.
	for(map<string, Tileset*>::iterator it = mTilesets.begin(); it != mTilesets.end(); ++it)
	{
		delete it->second;
	}
}

void TilesetManager::create()
{
    if(!mManager)
    {
        mManager = new TilesetManager();
    }
}

unsigned int TilesetManager::determineSize()
{
    return (unsigned int)mManager->mData.size();
}

const string TilesetManager::getCurrentResourceName()
{
    // If we are currently debugging, just note that a tileset is loading.
    return (Game::isDebug()) ? (*(mManager->mData.begin())).name : "Unknown Tileset";
}

bool TilesetManager::loadResource()
{
    // If the data is empty, return false
    if(mManager->mData.empty())
    {
        return false;
    }

    // Get the first entry in the list.
    list<TilesetData>::iterator it = mManager->mData.begin();

    // Create and configure the new tileset.
    Tileset* tmp = new Tileset(*it);

	// Add the new tileset.
	mManager->mTilesets[(*it).name] = tmp;

    // Remove that entry.
    mManager->mData.pop_front();

    // Return true if more resources need to be loaded.
    return (mManager->mData.empty()) ? false : true;
}

void TilesetManager::terminate()
{
    delete mManager;
    mManager = 0;
}

const Tileset* TilesetManager::get(const string& key)
{
    // Make sure the manager exists.
    if(!mManager)
    {
        throw runtime_error("TilesetManager::get() -> TilesetManager has not yet been created.");
    }

    // Check to make sure the tileset exists.
    map<string, Tileset*>::const_iterator it = mManager->mTilesets.find(key);

    // If the iterator is not at the end of the map, then the tileset was found.  Return it.
    if(it != mManager->mTilesets.end())
    {
        return mManager->mTilesets[key];
    }
    else
    {
        // Tileset not found, error.
        throw runtime_error("TilesetManager::get() -> Tileset '" + key + "' not found.");
    }
}

TilesetManager* TilesetManager::mManager = 0;

const char* TilesetManager::FILE_TILESET_DATA = "tilesets.dat";
