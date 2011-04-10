/*
 * Map.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "Map.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

#include "../Managers/AnimationManager.hpp"
#include "../Math/Base64Functions.hpp"
#include "../Entities/Entity.hpp"
#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Managers/TilesetManager.hpp"
#include "../Game/TileType.hpp"

using std::ifstream;
using std::runtime_error;
using std::string;
using std::vector;

const string MAP_MAPDIRECTORY = "Maps/";
const string MAP_KEYWORD_TILESET = "TILESET";
const string MAP_KEYWORD_WIDTH = "WIDTH";
const string MAP_KEYWORD_HEIGHT = "HEIGHT";
const string MAP_KEYWORD_LOWER = "LOWER";
const string MAP_KEYWORD_MIDDLE = "MIDDLE";
const string MAP_KEYWORD_UPPER1 = "UPPER1";
const string MAP_KEYWORD_UPPER2 = "UPPER2";
const string MAP_KEYWORD_UPPER3 = "UPPER3";

//Map::Map(const std::string& data) :
//									mWidth(0),
//									mHeight(0),
//									mTileset(0)
//{
//	// @todo implement
//	// Decode the data.
//	string decoded = decodeBase64(data);
//
//    /*
//     * The map string consists of the following separated by a colon:
//     * 1) The tileset name
//     * 2) The width
//     * 3) The height
//     * All characters after that denote the various tiles.  These characters
//     *  are provided in sets of 3 integers.  Each integer represents the GID
//     *  on the tileset to use.
//     */
//    string::size_type pos = 0;
//    mTileset = TilesetManager::get(extractDataLine(decoded, pos, CHAR_DELIMITER));
//    mWidth = toInt(extractDataLine(decoded, pos, CHAR_DELIMITER));
//    mHeight = toInt(extractDataLine(decoded, pos, CHAR_DELIMITER));
//
//    string tile_data = decodeBase64(extractDataLine(decoded, pos, CHAR_DELIMITER));
//
//    /* Load the map. */
//
//    // Computational variables.
//    string::size_type beg = 0;
//					  pos = 0; // Previously defined.
//    string levelData;
//
//    // Fill the lower level
//    beg = levelData.size();
//    levelData = tile_data.substr(beg, tile_data.find_first_of(CHAR_DELIMITER, beg) - beg);
//    while(pos != levelData.size())
//    {
//        mLMapData.push_back(toInt(extractDataLine(levelData, pos, CHAR_DELIMITER_MAP)));
//    }
//
//    // Fill the middle level
//    pos = 0;
//    beg = beg + levelData.size() + 1;
//    levelData = tile_data.substr(beg, tile_data.find_first_of(CHAR_DELIMITER, beg) - beg);
//    while(pos != levelData.size())
//    {
//        mMMapData.push_back(toInt(extractDataLine(levelData, pos, CHAR_DELIMITER_MAP)));
//    }
//
//    // Fill the first upper level
//    pos = 0;
//    beg = beg + levelData.size() + 1;
//    levelData = tile_data.substr(beg, tile_data.find_first_of(CHAR_DELIMITER, beg) - beg);
//    while(pos != levelData.size())
//    {
//        mU1MapData.push_back(toInt(extractDataLine(levelData, pos, CHAR_DELIMITER_MAP)));
//    }
//
//    // Fill the second upper level
//    pos = 0;
//    beg = beg + levelData.size() + 1;
//    levelData = tile_data.substr(beg, tile_data.find_first_of(CHAR_DELIMITER, beg) - beg);
//    while(pos != levelData.size())
//    {
//        mU2MapData.push_back(toInt(extractDataLine(levelData, pos, CHAR_DELIMITER_MAP)));
//    }
//
//    // Fill the third upper level
//    pos = 0;
//    beg = beg + levelData.size() + 1;
//    levelData = tile_data.substr(beg, tile_data.find_first_of(CHAR_DELIMITER, beg) - beg);
//    while(pos != levelData.size())
//    {
//        mU3MapData.push_back(toInt(extractDataLine(levelData, pos, CHAR_DELIMITER_MAP)));
//    }
//
//    // Make sure the data loaded correctly.
//    if(mLMapData.size() != (mWidth * mHeight))
//    {
//        throw runtime_error("Map::mLoadMap() -> Map layer sizes do not match the provided map area: "
//                            + toString(mWidth * mHeight) + " != " + toString(mLMapData.size()));
//    }
//
//    // Now that the data is loaded and the data is valid, generate the map tiles.
//    mGenerateMapTiles();
//}

Map::Map(const string& mapFile) :
								  mWidth(0),
								  mHeight(0),
								  mTileset(0)
{
	// The full map filename.
	string map_file = MAP_MAPDIRECTORY + mapFile;

	// Load the map file.
	ifstream file(map_file.c_str(), ifstream::in);
	if(!file.good())
	{
		throw runtime_error("Map() -> Map file not found: " + map_file);
	}

	// Iterate throughout the file and load the basic data
	string current_line;
	while(!file.eof())
	{
    	// Get the current line.
    	getline(file, current_line);

    	// Ignore comments and empty lines.
    	if(current_line.empty() || current_line[0] == '#')
    	{
    		continue;
    	}

    	// This line has data on it, start by getting the keyword.
    	string::size_type pos = 0;
    	string keyword = extractDataLine(current_line, pos, CHAR_DELIMITER);
    	if(keyword == MAP_KEYWORD_TILESET)
    	{
    		mTileset = TilesetManager::get(extractDataLine(current_line, pos, CHAR_DELIMITER));
    	}
    	else if(keyword == MAP_KEYWORD_WIDTH)
    	{
    		mWidth = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER));
    	}
    	else if(keyword == MAP_KEYWORD_HEIGHT)
    	{
    		mHeight = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER));
    	}
	}
	file.close();

    // Check the basic data.
    if(!mTileset)
    {
    	throw runtime_error("No " + MAP_KEYWORD_TILESET + " keyword provided for " + map_file);
    }
    // Make sure that the width and height were provided (they cannot be null.
    if(!mWidth)
    {
    	throw runtime_error("No " + MAP_KEYWORD_WIDTH + " keyword provided for " + map_file);
    }
    if(!mHeight)
    {
    	throw runtime_error("No " + MAP_KEYWORD_HEIGHT + " keyword provided for " + map_file);
    }

	// Re-open the map file.
	file.open(map_file.c_str(), ifstream::in);
	if(!file.good())
	{
		throw runtime_error("Map() -> Map file not found: " + map_file);
	}

    // Get the tile sizes.
    int tile_width = mTileset->getWidth(),
        tile_height= mTileset->getHeight();

	// Now get the layer data.
    while(!file.eof())
    {
    	// Get the current line.
    	getline(file, current_line);

    	// Ignore comments and empty lines.
    	if(current_line.empty() || current_line[0] == '#')
    	{
    		continue;
    	}

    	// This line has data on it, start by getting the keyword.
    	string::size_type pos = 0;
    	string keyword = extractDataLine(current_line, pos, CHAR_DELIMITER);
    	if(keyword == MAP_KEYWORD_LOWER)
    	{
    		// Make sure the layer is clear.
    		mLMap.clear();

    		// The tile position (not pixel position).
    		unsigned int x = 0,
						 y = 0;
    		while(pos != current_line.size())
    		{
    			// Get the actual position of the tiles.
                unsigned int xPos = x * tile_width;
                unsigned int yPos = y * tile_height;

                // Create the tile, set its position, and add it to the layer.
                Tile tile = mTileset->at(toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)));
                tile.setPosition(xPos, yPos);
    			mLMap.push_back(tile);

    			// Increment the x and y tile positions, if appropriate.
    			++x;
    			if(x == mWidth)
    			{
    				++y;
    				x = 0;
    			}
    		}
    	}
    	else if(keyword == MAP_KEYWORD_MIDDLE)
    	{
    		// Make sure the layer is clear.
    		mMMap.clear();

    		// The tile position (not pixel position).
    		unsigned int x = 0,
						 y = 0;
    		while(pos != current_line.size())
    		{
    			// Get the actual position of the tiles.
                unsigned int xPos = x * tile_width;
                unsigned int yPos = y * tile_height;

                // Create the tile, set its position, and add it to the layer.
                Tile tile = mTileset->at(toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)));
                tile.setPosition(xPos, yPos);
    			mMMap.push_back(tile);

    			// Increment the x and y tile positions, if appropriate.
    			++x;
    			if(x == mWidth)
    			{
    				++y;
    				x = 0;
    			}
    		}
    	}
    	else if(keyword == MAP_KEYWORD_UPPER1)
    	{
    		// Make sure the layer is clear.
    		mU1Map.clear();

    		// The tile position (not pixel position).
    		unsigned int x = 0,
						 y = 0;
    		while(pos != current_line.size())
    		{
    			// Get the actual position of the tiles.
                unsigned int xPos = x * tile_width;
                unsigned int yPos = y * tile_height;

                // Create the tile, set its position, and add it to the layer.
                Tile tile = mTileset->at(toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)));
                tile.setPosition(xPos, yPos);
    			mU1Map.push_back(tile);

    			// Increment the x and y tile positions, if appropriate.
    			++x;
    			if(x == mWidth)
    			{
    				++y;
    				x = 0;
    			}
    		}
    	}
    	else if(keyword == MAP_KEYWORD_UPPER2)
    	{
    		// Make sure the layer is clear.
    		mU2Map.clear();

    		// The tile position (not pixel position).
    		unsigned int x = 0,
						 y = 0;
    		while(pos != current_line.size())
    		{
    			// Get the actual position of the tiles.
                unsigned int xPos = x * tile_width;
                unsigned int yPos = y * tile_height;

                // Create the tile, set its position, and add it to the layer.
                Tile tile = mTileset->at(toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)));
                tile.setPosition(xPos, yPos);
    			mU2Map.push_back(tile);

    			// Increment the x and y tile positions, if appropriate.
    			++x;
    			if(x == mWidth)
    			{
    				++y;
    				x = 0;
    			}
    		}
    	}
    	else if(keyword == MAP_KEYWORD_UPPER3)
    	{
    		// Make sure the layer is clear.
    		mU3Map.clear();

    		// The tile position (not pixel position).
    		unsigned int x = 0,
						 y = 0;
    		while(pos != current_line.size())
    		{
    			// Get the actual position of the tiles.
                unsigned int xPos = x * tile_width;
                unsigned int yPos = y * tile_height;

                // Create the tile, set its position, and add it to the layer.
                Tile tile = mTileset->at(toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)));
                tile.setPosition(xPos, yPos);
    			mU3Map.push_back(tile);

    			// Increment the x and y tile positions, if appropriate.
    			++x;
    			if(x == mWidth)
    			{
    				++y;
    				x = 0;
    			}
    		}
    	}
    	// If any unknown keywords were provided, warn the player.
    	else if(keyword != MAP_KEYWORD_TILESET && keyword != MAP_KEYWORD_WIDTH && keyword != MAP_KEYWORD_HEIGHT)
    	{
    		Logger::log(keyword + " is an unknown keyword in '" + map_file + "'.");
    	}
    }

    // Close the file.
    file.close();

    // Check the layers.
    // Make sure that the lower layer is not empty.
    if(mLMap.empty())
    {
    	throw runtime_error("No " + MAP_KEYWORD_LOWER + " keyword provided for " + map_file);
    }
    // The other layers can be empty, but warn the user.
    if(mMMap.empty())
    {
    	Logger::log(map_file + ": No middle layer provided.");
    }
    if(mU1Map.empty())
    {
    	Logger::log(map_file + ": No upper1 layer provided.");
    }
    if(mU2Map.empty())
    {
    	Logger::log(map_file + ": No upper2 layer provided.");
    }
    if(mU3Map.empty())
    {
    	Logger::log(map_file + ": No upper3 layer provided.");
    }

    // Finally, for layers that were provided, make sure their sizes are correct.
    if(mLMap.size() != mWidth * mHeight)
    {
    	throw runtime_error(map_file + ": Lower map layer is '" + toString(mLMap.size()) + "' but it should be '" + toString(mWidth * mHeight) + "'.");
    }
    if(!mMMap.empty() && mMMap.size() != mWidth * mHeight)
    {
    	throw runtime_error(map_file + ": Middle map layer is '" + toString(mMMap.size()) + "' but it should be '" + toString(mWidth * mHeight) + "'.");
    }
    if(!mU1Map.empty() && mU1Map.size() != mWidth * mHeight)
    {
    	throw runtime_error(map_file + ": Upper1 map layer is '" + toString(mU1Map.size()) + "' but it should be '" + toString(mWidth * mHeight) + "'.");
    }
    if(!mU2Map.empty() && mU2Map.size() != mWidth * mHeight)
    {
    	throw runtime_error(map_file + ": Upper2 map layer is '" + toString(mU2Map.size()) + "' but it should be '" + toString(mWidth * mHeight) + "'.");
    }
    if(!mU3Map.empty() && mU3Map.size() != mWidth * mHeight)
    {
    	throw runtime_error(map_file + ": Upper3 map layer is '" + toString(mU3Map.size()) + "' but it should be '" + toString(mWidth * mHeight) + "'.");
    }
}

Map::Map(const MapRule& rules) :
								 mWidth(rules.map_width),
								 mHeight(rules.map_height),
								 mTileset(TilesetManager::get(rules.tileset))
{
//	//@todo review and implement
//	//Generate the map based on the rule.
//    // Create an array of the size of the map data.
//    MapData map(rules.map_width, rules.map_height, TILE_FLOOR_A); // @todo need to implement floors
//
//    const unsigned int width = rules.map_width - 1;
//    const unsigned int height = rules.map_height - 1;
//
//    // The current number of rooms.
//    unsigned int number_of_rooms = 0;
//
//    unsigned int iteration = 0;
//
//    // While the current rooms is not equal to the maximum possible rooms, keep adding rooms.
//    while(number_of_rooms != rules.rooms)
//    {
//        // If this function has tried for long enough to add a room, just stop.
//        if(iteration == 1000)
//        {
//            Logger::log("Hit 1000");
//            break;
//        }
//
//        // Determine the width and height of the room.
//        // NOTE: The '+ 2' denotes the side walls. Therefore the minimum and maximum sizes denote the number of tiles in the room
//        // EXCLUDING the wall tiles.
//        // WARNING: If the map is too small and the room dimensions are large enough then the program can potentially get caught in an
//        //  infinite loop here, where the rooms already generated are spread out in such a way that any new rooms (which are of a certain
//        //  set size) are too large to place anywhere and not intersect with current rooms.
//        const unsigned int room_width = random(rules.room_width_min + 2, rules.room_width_max + 2);
//        const unsigned int room_height = random(rules.room_height_min + 2, rules.room_height_max + 2);
//
//        // Determine a random position to place the room.
//        const unsigned int x = random((const unsigned int)0, width);
//        const unsigned int y = random((const unsigned int)0, height);
//
//        // The bounds of the room.
//        // NOTE: I call these as separate variables to force using a signed int
//        // (because the y - room_width can go below 0, I need to ensure that number
//        //  will remain valid!)
//        int xMin = 0,
//            yMin = y - room_width,
//            xMax = x + room_width + room_height,
//            yMax = y + room_height;
//
//        // First, make sure that the bounding box of the new room doesn't go outside of the map's bounds.
//        if(xMin < 0 || yMin < 0 || xMax > int(width) || yMax > int(height))
//        {
//            continue;
//        }
//
//        // Now check to see if this room intersects with other rooms.
//        // NOTE: If an intersection is found, stop searching.
//        bool no_intersection = true;
//        unsigned int xPos = x;
//        unsigned int yPos = y;
//        while((xPos != x + room_width) && no_intersection)
//        {
//            no_intersection = map.isAreaClear(xPos++, yPos--, rules);
//        }
//        while((xPos != x + room_width + room_height) && no_intersection)
//        {
//            no_intersection = map.isAreaClear(xPos++, yPos++, rules);
//        }
//        while((xPos != x + room_height) && no_intersection)
//        {
//            no_intersection = map.isAreaClear(xPos--, yPos++, rules);
//        }
//        while((xPos != x) && no_intersection)
//        {
//            no_intersection = map.isAreaClear(xPos--, yPos--, rules);
//        }
//
//        // If the room doesn't intersect with another, then create the walls for it and add the new room.
//        if(no_intersection)
//        {
//            // Determine the number of doors in this room.
//            const unsigned int num_doors = random(rules.room_doors_min, rules.room_doors_max);
//
//            // Determine the perimeter of the room.
//            const unsigned int room_perimeter = (room_width * 2) + (room_height * 2) - 1; // -1 because we start counting at 0, not 1.
//
//            // Create a container for the walls of this room.
//            vector<TileType> walls(1, TILE_CORNER_WEST);
//            walls.insert(walls.end(), room_width - 1, TILE_NORTHWEST);
//            walls.push_back(TILE_CORNER_NORTH);
//            walls.insert(walls.end(), room_height - 1, TILE_NORTHEAST);
//            walls.push_back(TILE_CORNER_EAST);
//            walls.insert(walls.end(), room_width - 1, TILE_SOUTHEAST);
//            walls.push_back(TILE_CORNER_SOUTH);
//            walls.insert(walls.end(), room_height - 1, TILE_SOUTHWEST);
//
//            // For each door I need, determine the locations and add them to the array.
//            unsigned int i = 0;
//            while(i != num_doors)
//            {
//                // A section of wall.
//                TileType wall_section[3] = {TILE_NULL};
//
//                // A random room position.
//                unsigned int temp = random((unsigned int)1, room_perimeter - 1);
//
//                // Get the section of wall we are looking at (in the range of (temp - 1, temp + 1))
//                wall_section[0] = walls[temp - 1];
//                wall_section[1] = walls[temp];
//                wall_section[2] = walls[temp + 1];
//
//                // If the entire wall section is regular wall sections, then place the appropriate door tiles.
//                if(isWall(wall_section[0]) && isWall(wall_section[1]) && isWall(wall_section[2]))
//                {
//                    // Based on the wall we are currentlly on, add the door and hinges tiles.
//                    if(temp < room_width) // If this is the northwest wall...
//                    {
//                        walls[temp - 1] = TILE_NORTHWEST_DOORLEFT; // The first door 'hinge' tile
//                        walls[temp]     = TILE_NORTHWEST_DOORRIGHT; // The door tile itself
//                    }
//                    else if((temp > room_width) && (temp < room_width + room_height)) // If this is the northeast wall...
//                    {
//                        walls[temp - 1] = TILE_NORTHEAST_DOORLEFT; // The first door 'hinge' tile
//                        walls[temp]     = TILE_NORTHEAST_DOORRIGHT; // The door tile itself
//                    }
//                    else if((temp > room_width + room_height) && (temp < (room_width * 2) + room_height))
//                    {
//                        walls[temp - 1] = TILE_SOUTHEAST_DOORLEFT; // The first door 'hinge' tile
//                        walls[temp]     = TILE_SOUTHEAST_DOORRIGHT; // The door tile itself
//                    }
//                    else if((temp > (room_width * 2) + room_height) && (temp < (room_width * 2) + (room_height * 2)))
//                    {
//                        walls[temp - 1] = TILE_SOUTHWEST_DOORLEFT; // The first door 'hinge' tile
//                        walls[temp]     = TILE_SOUTHWEST_DOORRIGHT; // The door tile itself
//                    }
//                    i++; // Door added.
//                }
//            }
//
//            // Now draw the top left of the room.
//            unsigned int xPos = x;
//            unsigned int yPos = y;
//            vector<TileType>::iterator it = walls.begin();
//            while(xPos != x + room_width) // From the west corner to the north corner.
//            {
//                // NOTE: This door frame displays at the same level as the wall it is attached to.
//                //  This means that I need to move it up to the next level before I place it.
//                // (The standard is to add it afterwards)
//                if(*it == TILE_NORTHWEST_DOORRIGHT)
//                {
//                    map.set(xPos++, --yPos, *it++);
//                }
//                else
//                {
//                    map.set(xPos++, yPos--, *it++);
//                }
//            }
//            // Now draw the top right of the room.
//            while(xPos != x + room_width + room_height) // From one past the north corner to the east corner.
//            {
//                if(*it == TILE_NORTHEAST_DOORLEFT)
//                {
//                    // NOTE: As with TILE_NORTHWEST_DOORRIGHT, this tile needs to be at the same
//                    //  level as the wall it is on.  --yPos will put this tile back to the same
//                    //  height as the last tile, but because this wall heads south, yPos needs
//                    //  to be incremented for the next tile AND compensated for this one (hence
//                    //  += 2 instead of ++.
//                    map.set(xPos++, --yPos, *it++);
//                    yPos += 2;
//                }
//                else
//                {
//                    map.set(xPos++, yPos++, *it++);
//                }
//            }
//            // Now draw the bottom right of the room.
//            while(xPos != x + room_height) // From one past the east corner to one before the south corner.
//            {
//                if(*it == TILE_SOUTHEAST_DOORLEFT)
//                {
//                    // NOTE: Same setup as TILE_NORTHEAST_DOORLEFT.
//                    //  The -- prefix is to place this tile at the same level as the last wall tile
//                    //  this frame is attached to.  The += 2 is to compensate for this positional
//                    //  difference for the next tile (and each subsequent tile)
//                    map.set(xPos--, --yPos, *it++);
//                    yPos += 2;
//                }
//                else
//                {
//                    map.set(xPos--, yPos++, *it++);
//                }
//            }
//            // The south corner.
//            map.set(xPos--, --yPos, *it++); // NOTE: Unlike the other tiles, the south corner only moves on the X axis.
//            // Now draw the bottom left of the room.
//            while(xPos != x) // From one past the south corner to one before the west corner (full circle)
//            {
//                if(*it == TILE_SOUTHWEST_DOORRIGHT)
//                {
//                    map.set(xPos--, --yPos, *it++);
//                }
//                else
//                {
//                    map.set(xPos--, yPos--, *it++);
//                }
//            }
//
//            // The room has been drawn.
//            number_of_rooms++;
//        }
//
//        // Another iteration has passed.
//        iteration++;
//    }
//
//    // Convert the map into a vector of the same data.
//    vector<TileType> mapData = map.data;
//
//    // Delete and clear the data lists and fill them with blank tiles.
//    mU3MapData = vector<unsigned int>(mapData.size(), 0);
//    mU2MapData = vector<unsigned int>(mapData.size(), 0);
//    mU1MapData = vector<unsigned int>(mapData.size(), 0);
//    mMMapData  = vector<unsigned int>(mapData.size(), 0);
//    mLMapData  = vector<unsigned int>(mapData.size(), 0);
//
//    // Convert the width to an integer.
//    int sWidth = int(width);
//
//    for(vector<TileType>::size_type i = 0; i != mapData.size(); ++i)
//    {
//        int pos = int(i);
//    	TileData dat = mTileset->getTileData(mapData[i]);
//    	if(pos > 3 * sWidth + 3) mU3MapData.at(pos - (3 * sWidth) - 3) = dat.u3;
//    	if(pos > 2 * sWidth + 2) mU2MapData.at(pos - (2 * sWidth) - 2) = dat.u2;
//    	if(pos > sWidth + 1) mU1MapData.at(pos - sWidth - 1) = dat.u1;
//    	mMMapData.at(pos) = dat.m;
//    	mLMapData.at(pos) = dat.l;
//    }
//
//    // Now that the data has been generated, regenerate the tiles.
//    mGenerateMapTiles();
}

void Map::drawLower(Renderer& renderer)
{// @todo Are only the tiles which could be seen being drawn?
    // Draw the lower map.
    for(MapLayer::iterator it = mLMap.begin(); it != mLMap.end(); ++it)
    {
    	it->draw(renderer);
    }
}

void Map::drawMiddle(Renderer& renderer)
{// @todo Are only the tiles which could be seen being drawn?
    // Draw the middle map.
    // NOTE: The middle map is raised a tile to show the isometricity.
    for(MapLayer::iterator it = mMMap.begin(); it != mMMap.end(); ++it)
    {
    	it->draw(renderer);
    }
}

void Map::drawUpper(Renderer& renderer)
{// @todo Are only the tiles which could be seen being drawn?
    // Draw the upper map.
    // NOTE: The upper maps are sequentially raised by an appropriate height to show isometric depth.
    for(MapLayer::iterator it = mU1Map.begin(); it != mU1Map.end(); ++it)
    {
    	it->draw(renderer);
    }
    for(MapLayer::iterator it = mU2Map.begin(); it != mU2Map.end(); ++it)
    {
		it->draw(renderer);
    }
    for(MapLayer::iterator it = mU3Map.begin(); it != mU3Map.end(); ++it)
    {
    	it->draw(renderer);
    }
}

string Map::extract() const
{// @todo implement... actually, if the maps are saved separately, I don't need to save this, do I?
    // The return string.
    string ret = mTileset->getName() + CHAR_DELIMITER + toString(mWidth) + CHAR_DELIMITER
                 + toString(mHeight) + CHAR_DELIMITER;

//    // Add the tile data.
//    string tile_data;
//
//    // Ensure the sizes are correct.
//    if(mLMapData.size() != mMMapData.size() || mLMapData.size() != mU1MapData.size() ||
//       mLMapData.size() != mU2MapData.size() || mLMapData.size() != mU3MapData.size())
//    {
//        throw runtime_error("Map::extract() -> One or more map data containers have an incorrect size.");
//    }
//
//    // Now, fill the return container with the map data.
//    for(vector<uint>::const_iterator it = mLMapData.begin(); it != mLMapData.end(); ++it)
//    {
//        tile_data += toString(*it) + CHAR_DELIMITER_MAP;
//    }
//    tile_data += CHAR_DELIMITER;
//    for(vector<uint>::const_iterator it = mMMapData.begin(); it != mMMapData.end(); ++it)
//    {
//        tile_data += toString(*it) + CHAR_DELIMITER_MAP;
//    }
//    tile_data += CHAR_DELIMITER;
//    for(vector<uint>::const_iterator it = mU1MapData.begin(); it != mU1MapData.end(); ++it)
//    {
//        tile_data += toString(*it) + CHAR_DELIMITER_MAP;
//    }
//    tile_data += CHAR_DELIMITER;
//    for(vector<uint>::const_iterator it = mU2MapData.begin(); it != mU2MapData.end(); ++it)
//    {
//        tile_data += toString(*it) + CHAR_DELIMITER_MAP;
//    }
//    tile_data += CHAR_DELIMITER;
//    for(vector<uint>::const_iterator it = mU3MapData.begin(); it != mU3MapData.end(); ++it)
//    {
//        tile_data += toString(*it) + CHAR_DELIMITER_MAP;
//    }
//    tile_data += CHAR_DELIMITER;
//
//    // Decode the tile data and add it to the return string.
//    ret += encodeBase64(tile_data);

    // Return the data.
    return ret;
}

int Map::getWidth() const
{
    return (mTileset) ? mWidth * mTileset->getWidth() : 0;
}

int Map::getHeight() const
{
    return (mTileset) ? mHeight * mTileset->getHeight() : 0;
}

bool Map::isOnMap(int x, int y, int width, int height) const
{
    return x >= 0 && y >= 0 && x + width <= getWidth() && y + height <= getHeight();
}

bool Map::isOutOfBounds(const Entity& entity) const
{
    return !isOnMap(entity.getX(), entity.getY(), entity.getWidth(), entity.getHeight());
}

bool Map::isOutOfBounds(const Rectangle& area) const
{
    return !isOnMap(area.vector.x, area.vector.y, area.width, area.height);
}
