/*
 * GameData.cpp
 *
 *  Created on: Jul 9, 2009
 *      Author: alienjon
 */
#include "GameData.hpp"

#include <list>
#include <stdexcept>

#include "../Math/Base64Functions.hpp"
#include "../Entities/Creatures/Creature.hpp"
#include "../Math/Ellipse.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Non-Creatures/Flashlight.hpp"
#include "../Entities/Non-Creatures/Item.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../MapInfo/MapRule.hpp"
#include "../Entities/Non-Creatures/Object.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"

using std::endl;
using std::ifstream;
using std::invalid_argument;
using std::list;
using std::map;
using std::ofstream;
using std::runtime_error;
using std::string;

// File information.
const string GAMEDATA_METALEVEL = "levels.dat";
const string GAMEDATA_LEVEL_PREFIX = "Levels/";
const string GAMEDATA_LEVEL_EXTENSION = ".lvl";
const string FILE_ENTITYTEMPLATES = "EntityTemplates.dat";
const string GAMEDATA_PREFIX_FIRSTLEVEL = "1";

// Keywords.
const string KEYWORD_AREA 		  = "AREA";
const string KEYWORD_CREATURE	  = "CREATURE";
const string KEYWORD_LIGHT_RECT	  = "LIGHT_RECT";
const string KEYWORD_LIGHT_QUAD	  = "LIGHT_QUAD";
const string KEYWORD_LIGHT_ELIP   = "LIGHT_ELIP";
const string KEYWORD_MAP		  = "MAP";
const string KEYWORD_OBJECT		  = "OBJECT";
const string KEYWORD_ITEM		  = "ITEM";
const string KEYWORD_PLAYER_START = "PLAYER_START";
const string KEYWORD_PLOT		  = "PLOT";
const string KEYWORD_PORTAL		  = "PORTAL";

GameData::GameData() :
	mPlayer(0),
    mLevel(0)
{
}

GameData::GameData(const GameData& data)
{
	throw runtime_error("GameData(GameData&) -> Copying a game data object.  This shouldn't happen.");
}

GameData::~GameData()
{
    // Delete the current level.
    delete mLevel;
    mLevel = 0;

	// Delete the loaded entities after deleting the level, as deleting the level depends on those entities
    // existing (EnvironmentData, for example, needs to remove itself as a listener to the entities)
	mDeleteEntities();
}

GameData& GameData::operator=(const GameData& data)
{
	throw runtime_error("GameData::operator=() -> Assigning a GameData object.  This shouldn't happen.");
}

void GameData::mDeleteEntities()
{
	// Delete all entities EXCEPT tiles.
	for(list<Entity*>::iterator it = mLoadedEntities.begin(); it != mLoadedEntities.end(); ++it)
	{
		if((*it)->getType() != ENTITY_TILE)
		{
			delete *it;
		}
	}
	mPlayer = 0; // The player will have been deleted as well, so clear it here.

	// Clear the entities.
	mLoadedEntities.clear();
	mLoadedEntities.push_back(mPlayer);
}

const LevelData& GameData::mFindLevel(const string& levelName)
{
	// Find the level with the provided name.
	map<string, LevelData>::iterator pos = mLevels.find(levelName);

	if(pos == mLevels.end())
	{
		throw runtime_error("GameData::mFindLevel() -> Level with name '" + levelName + "' not found.");
	}

	return pos->second;
}

Entity* GameData::mGetEntity(const string& name)
{
	for(list<Entity*>::iterator it = mLoadedEntities.begin(); it != mLoadedEntities.end(); ++it)
	{
		if((*it)->getName() == name)
		{
			return *it;
		}
	}

	return 0;
}

const EntityTemplate& GameData::mGetEntityTemplate(const string& keyword)
{
	// Find the keyword or error.
	for(list<EntityTemplate>::const_iterator it = mEntityTemplates.begin(); it != mEntityTemplates.end(); ++it)
	{
		if(it->keyword == keyword)
		{
			return *it;
		}
	}

	// Not found, error.
	throw runtime_error("GameData::mGetEntityTemplate() -> Template with keyword '" + keyword + "' not found.");
}

void GameData::mSaveLevelState()
{//@todo need to implement saving levels
//    // If the level number is greater than the levels currently played, add it to the end of the list.
//    if(mCurrentLevel >= mLevels.size())
//    {
//        mLevels.push_back(encodeBase64(mLevel->extractData()));
//    }
//    // Otherwise, store the level.
//    else
//    {
//        mLevels.at(mCurrentLevel) = encodeBase64(mLevel->extractData());
//    }
}

Creature* GameData::createCreature(const string& name, const string& tmpl, const string& align, unsigned int health, unsigned int defense)
{
	Creature* entity = new Creature(name, mGetEntityTemplate(tmpl), align, health, defense);
	mLoadedEntities.push_back(entity);
	return entity;
}

Flashlight* GameData::createFlashlight(const string& name, const string& tmpl, unsigned int distance, unsigned int span)
{
	Flashlight* light = new Flashlight(name, mGetEntityTemplate(tmpl), distance, span);
	mLoadedEntities.push_back(light);
	return light;
}

Item* GameData::createItem(const string& name, const string& tmpl)
{
	Item* item = new Item(name, mGetEntityTemplate(tmpl));
	mLoadedEntities.push_back(item);
	return item;
}

Object* GameData::createObject(const string& name, const string& tmpl)
{
	Object* object = new Object(name, mGetEntityTemplate(tmpl));
	mLoadedEntities.push_back(object);
	return object;
}

Entity* GameData::getEntityById(const unsigned int& id)
{
	for(list<Entity*>::iterator it = mLoadedEntities.begin(); it != mLoadedEntities.end(); ++it)
	{
		if((*it)->getId() == id)
		{
			return *it;
		}
	}

	return 0;
}

Entity* GameData::getEntityByName(const string& name)
{
	for(list<Entity*>::iterator it = mLoadedEntities.begin(); it != mLoadedEntities.end(); ++it)
	{
		if((*it)->getName() == name)
		{
			return *it;
		}
	}

	return 0;
}

Level* GameData::getLevel(const string& levelName)
{
	if(Game::isDebug())
	{
		Logger::log("Loading level " + levelName);
	}

	// Delete the current level and create the new one.
	delete mLevel;
	mLevel = new Level(mFindLevel(levelName));

	// Return the found level.
	return mLevel;
}

Player* GameData::getPlayer() const
{
	return mPlayer;
}

Level* GameData::load()
{
	// Create the player.
	delete mPlayer;
	mPlayer = new Player;
	mLoadedEntities.push_back(mPlayer);

	// The name of the first level and the starting point for the player.
	string first_level;
	Vector player_start;

	// A collection of level names.
	list<string> levels;

	// Load the levels from the meta level data file.
    ifstream file(GAMEDATA_METALEVEL.c_str(), ifstream::in);

    // If the file opened successfully, then we are loading a game, otherwise start a new one.
    if(!file.good())
    {
        // Bad file opening.
        throw runtime_error("GameData() -> Problem opening '" + GAMEDATA_METALEVEL + "'.");
    }

    // The current level name.
    string meta_file_level;

    // Iterate throughout the file and store each line as the name of a different level file.
    while(!file.eof())
    {
    	// Get the line.
    	getline(file, meta_file_level);

    	// Ignore comments.
    	if(meta_file_level.empty() || meta_file_level[0] == '#')
    	{
    		continue;
    	}
    	// If the line starts with the 1st level prefix, then load the first level information.
    	else if(meta_file_level.find_first_of(GAMEDATA_PREFIX_FIRSTLEVEL) != string::npos)
    	{
    		// Load the name of the first level.
    		string::size_type pos = 0;
    		extractDataLine(meta_file_level, pos, CHAR_DELIMITER);
    		first_level = extractDataLine(meta_file_level, pos, CHAR_DELIMITER);

    		// Load the initial point at which the player enters the level.@todo asfd
    		int x = toInt(extractDataLine(meta_file_level, pos, CHAR_DELIMITER)),
    			y = toInt(extractDataLine(meta_file_level, pos, CHAR_DELIMITER));
    		player_start = Vector(x, y);
    		continue;
    	}
    	else
    	{
    		levels.push_back(GAMEDATA_LEVEL_PREFIX + meta_file_level + GAMEDATA_LEVEL_EXTENSION);
    	}
    }

    // Close the file.
    file.close();

	// Open the data file and load the objects.
    file.open(FILE_ENTITYTEMPLATES.c_str(), ifstream::in);

    // If the file opened successfully, then we are loading a game, otherwise start a new one.
    if(!file.good())
    {
        // Bad file opening.
        throw runtime_error("GameData() -> Problem opening '" + FILE_ENTITYTEMPLATES + "'.");
    }

    // Iterate throughout the file and load the templates.
    string current_line;
    while(!file.eof())
    {
    	// Get the line.
    	getline(file, current_line);

    	// Ignore comments and empty lines.
    	if(current_line.empty() || current_line[0] == '#')
    	{
    		continue;
    	}

    	// Get the keyword.
    	string::size_type pos = 0;
    	string keyword	 = extractDataLine(current_line, pos, CHAR_DELIMITER),
    		   animation = extractDataLine(current_line, pos, CHAR_DELIMITER);
    	int cX = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)),
    		cY = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)),
    		cW = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER)),
    		cH = toInt(extractDataLine(current_line, pos, CHAR_DELIMITER));
    	mEntityTemplates.push_back(EntityTemplate(keyword, animation, Rectangle(cX, cY, cW, cH)));
    }

    // Close the file.
    file.close();

    // For each level, open and store the level data.
    string level_line;
    unsigned int level = 1;
    for(list<string>::iterator it = levels.begin(); it != levels.end(); ++it, ++level)
    {
    	// Open the file, but error if the file is not found.
    	file.open(it->c_str(), ifstream::in);
    	if(!file.good())
    	{
    		throw runtime_error("GameData() -> Error loading level '" + *it + "'.");
    	}

    	// The level data.
    	LevelData levelData;

    	// Process the file.
    	while(!file.eof())
    	{
			// Get the current line.
			getline(file, level_line);

			// Ignore comments.
			if(level_line.empty() || level_line[0] == '#')
			{
				continue;
			}

			// Parse, based on the keyword.
			string::size_type pos = 0;
			string keyword = extractDataLine(level_line, pos, CHAR_DELIMITER);
			if(keyword == KEYWORD_AREA)
			{
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				unsigned int w = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
							 h = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				levelData.addArea(name, Rectangle(x, y, w, h));
			}
			else if(keyword == KEYWORD_PORTAL) // @todo implement
			{
				levelData.addPortal(extractDataLine(level_line, pos, CHAR_DELIMITER),
				                    extractDataLine(level_line, pos, CHAR_DELIMITER),
				                    extractDataLine(level_line, pos, CHAR_DELIMITER));
			}
			else if(keyword == KEYWORD_MAP)
			{
				levelData.mapData = extractDataLine(level_line, pos, CHAR_DELIMITER);
			}
			else if(keyword == KEYWORD_CREATURE)
			{
				// Get the name and position.
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));

				// Get the creature by its name.
				Entity* entity = mGetEntity(name);

				// If the entity wasn't found then try creating it.
				if(!entity)
				{
					try
					{
						string tmpl = extractDataLine(level_line, pos, CHAR_DELIMITER),
							   align = extractDataLine(level_line, pos, CHAR_DELIMITER);
						unsigned int health = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
									 defense= toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
						entity = createCreature(name, tmpl, align, health, defense);
					}
					catch(runtime_error& e)
					{
						Logger::error(e);
						continue;
					}
				}
				levelData.addEntity(entity);
				levelData.entry_points[entity->getId()] = Vector(x, y);
			}
			else if(keyword == KEYWORD_OBJECT)
			{
				// Get the entity's name and position.
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER),
					   tmpl = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));

				// Get the entity, but if it was not found, then create it.
				Entity* entity = mGetEntity(name);
				if(!entity)
				{
					try
					{
						entity = createObject(name, tmpl);
					}
					catch(runtime_error& e)
					{
						Logger::error(e);
						continue;
					}
				}
				levelData.addEntity(entity);
				levelData.entry_points[entity->getId()] = Vector(x, y);
			}
			else if(keyword == KEYWORD_ITEM)
			{
				// Get the entity's name and position.
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER),
					   tmpl = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));

				// Get the entity, but if it was not found, then create it.
				Entity* entity = mGetEntity(name);
				if(!entity)
				{
					try
					{
						entity = createItem(name, tmpl);
					}
					catch(runtime_error& e)
					{
						Logger::error(e);
						continue;
					}
				}
				levelData.addEntity(entity);
				levelData.entry_points[entity->getId()] = Vector(x, y);
			}
			else if(keyword == KEYWORD_PLAYER_START)
			{
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				levelData.addEntity(mPlayer);
				levelData.entry_points[mPlayer->getId()] = Vector(x, y);
			}
			else if(keyword == KEYWORD_LIGHT_RECT)
			{
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				unsigned int w = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
							 h = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				levelData.addLightQuad(name,
				                       Quadrilateral(Vector(x, y),
				                                     Vector(x + w, y),
				                                     Vector(x + w, y + h),
				                                     Vector(x, y + h)));
			}
			else if(keyword == KEYWORD_LIGHT_QUAD)
			{
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER);
				Vector p1, p2, p3, p4;
				p1.x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p1.y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p2.x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p2.y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p3.x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p3.y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p4.x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				p4.y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				levelData.addLightQuad(name, Quadrilateral(p1, p2, p3, p4));
			}
			else if(keyword == KEYWORD_LIGHT_ELIP)
			{
				string name = extractDataLine(level_line, pos, CHAR_DELIMITER);
				int x = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
					y = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				unsigned int width = toInt(extractDataLine(level_line, pos, CHAR_DELIMITER)),
							 height= toInt(extractDataLine(level_line, pos, CHAR_DELIMITER));
				levelData.addLightElip(name, Ellipse(x, y, width, height));
			}
			else
			{
				Logger::warn("Invalid level keyword: " + keyword);
			}
    	}

    	// Make sure the level is valid.
    	if(levelData.mapData.empty())
    	{
    		Logger::error((*it) + " does not have a map provided.");
    	}

    	// Add the player.
		levelData.addEntity(mPlayer);

    	// Add the level data.
		string nme = extractFilename(*it);
		levelData.name = nme;
    	mLevels[nme] = levelData;

    	// Close the file.
    	file.close();
    }

    // @todo need to implement game loading, right now only new games can be started.
	if(Game::isDebug())
	{
		Logger::log("Starting a new game.");
	}

	Level* new_level = getLevel(first_level);
	new_level->load(player_start);
	return new_level;
}

//Level* GameData::loadGame(const string& filename)
//{@todo need to implement loading.
//    // Clear out any current data.
//    delete mLevel;
//    mLevel = 0;
//    mLevels.clear();
//    delete mPlayer;
//    mPlayer = 0;
//
//    // Try opening the file.
//    if(!filename.empty())
//    {
//        mFilename = filename;
//    }
//    string f = "Saved/" + mFilename;
//    ifstream file(f.c_str(), ifstream::in);
//
//    // If the file opened successfully, then we are loading a game, otherwise start a new one.
//    if(!file.good())
//    {
//        // Bad file opening.
//        throw runtime_error("GameData::load() -> Problem opening '" + mFilename + "'.");
//    }
//
//    // Get the meta line.
//    string data;
//    getline(file, data);
//    string::size_type pos = 0;
//
//    // Get the meta data.
//    mDifficulty   = getDifficulty(extractDataLine(data, pos, CHAR_DELIMITER));
//    mCurrentLevel = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mPlayer       = new Player(decodeBase64(extractDataLine(data, pos, CHAR_DELIMITER)));
//
//    // Now load each line of the file as a different level (each line should be a different base64 key representing the level)
//    while(pos != data.size())
//    {
//        mLevels.push_back(extractDataLine(data, pos, CHAR_DELIMITER));
//    }
//
//    // Close the file.
//    file.close();
//
//    // Create, set and return the current level.
//	pos = 0;
//	string full_level = mGet(mCurrentLevel),
//		   levelData = extractDataLine(full_level, pos, CHAR_DELIMITER),
//		   mapData = extractDataLine(full_level, pos, CHAR_DELIMITER);
//    mLevel = new Level(levelData, mapData, mPlayer);
//
//    // Indicate that the game was loaded.
//    if(Game::isDebug())
//    {
//        Logger::log("Loading saved game: '" + mFilename + "'");
//    }
//
//    return mLevel;
//}

void GameData::plotOccurance(const PlotEvent& event)
{
	// Check for requests to go to a different level.
	if(event.getKeyword() == KEYWORD_LOAD_AREA)
	{
		// @todo load a different level
		Logger::log("GameData::plotOccurance() -> Load a new level?  Need to load a new level?");
	}
}

void GameData::saveGame(const string& filename)
{//@todo need to implement saving and loading.
//    // Open the file for saving.
//    if(!filename.empty())
//    {
//        mFilename = filename;
//    }
//
//    string f = "Saved/" + mFilename;
//    ofstream file(f.c_str(), ofstream::out | ofstream::trunc);
//
//    if(!file.good())
//    {
//        Logger::log("Unable to save game: '" + mFilename + "' doesn't exist.");
//        return;
//    }
//
//    // Before saving the data, save meta-game information in the following order (separated by delimiters):
//    //  game difficulty
//    //  current level being played in
//    //  the player's data
//    string meta = getDifficulty(mDifficulty) + CHAR_DELIMITER + toString(mCurrentLevel) + CHAR_DELIMITER
//                  + encodeBase64(mPlayer->extract()) + CHAR_DELIMITER;
//
//    // Save the current level state and then add the levels to the output string.
//    mSaveLevelState();
//    for(vector<string>::size_type i = 0; i != mLevels.size(); ++i)
//    {
//        meta += mLevels[i] + CHAR_DELIMITER;
//    }
//
//    // Store the data to the file.
//    file << meta << endl;
//
//    // Close the file.
//    file.close();
//
//    // Indicate that the game was saved.
//    if(Game::isDebug())
//    {
//        Logger::log("Saving game to file: '" + mFilename + "'");
//    }
}
// @todo evaluate these
const string LEVEL_NULL  = "";
