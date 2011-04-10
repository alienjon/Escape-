/*
 * GameData.hpp
 *
 *  Created on: Jul 9, 2009
 *      Author: alienjon
 */

#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <fstream>
#include <list>
#include <map>
#include <string>

#include "../Entities/Templates/EntityTemplate.hpp"
#include "../Game/Game.hpp"
#include "../LevelInfo/Level.hpp"
#include "../LevelInfo/LevelData.hpp"
#include "../Entities/Creatures/Player.hpp"
#include "../PlotInfo/PlotEvent.hpp"
#include "../Listeners/PlotListener.hpp"
#include "../Math/Vector.hpp"

class Creature;
class Entity;
class Flashlight;
class Object;

/**
 * @brief The game data is the game's interface to the filesystem to save and load games.
 *
 * The game data contains all stored level information and saves levels during gameplay.
 * Then, as the player asks for it, it is through the GameData object that information is
 * saved to the filesystem.
 */
class GameData : public PlotListener
{
    public:
    /**
     * @brief Game data is the interface with the saved game file and can load information from the file.
     */
    GameData();
    GameData(const GameData& data);
    ~GameData();
    GameData& operator=(const GameData& data);

    /**
     * @brief Create an entity.
     * @param name The name of the entity.
     * @param tmpl The template name.
     * @param align The creature's alignment.
     * @param health The maximum health.
     * @param defense The maximum defense.
     * @return The created creature.
     */
    Creature* createCreature(const std::string& name, const std::string& tmpl, const std::string& align, unsigned int health, unsigned int defense);

    /**
     * @brief Create a flashlight.
     * @param name The name for the flashlight.
     * @param tmpl The animation template for the flashlight to be shown when the flashlight is on the ground.
     * @param distance The distance the light shines.
     * @param span The span the light shines.
     * @return The created flashlight.
     */
    Flashlight* createFlashlight(const std::string& name, const std::string& tmpl, unsigned int distance, unsigned int span);

    /**
     * @brief Create a generic item.
     * @param name The name for the item.
     * @param tmpl The item's template.
     * @return The created item.
     */
    Item* createItem(const std::string& name, const std::string& tmpl);

    /**
     * @brief Create an object.
     * @param name The name of the object.
     * @param tmpl The object's template.
     * @return The created object.
     */
    Object* createObject(const std::string& name, const std::string& tmpl);

    /**
     * @brief Get an entity with the provided ID.
     * @param id The id of the entity to retrieve.
     * @return The entity with the provided id, or null if it does not exist.
     */
    Entity* getEntityById(const unsigned int& id);

    /**
     * @brief Get the entity with the requested name.
     * @param name The name.
     * @return The entity with the requested name, or null if it does not yet exist.
     */
    Entity* getEntityByName(const std::string& name);

    /**
     * @brief Delete the current level and load the requested one.
     * @param levelName The name of the level to retrieve.
     *
     * @note Calling this method with a blank string or without any parameters returns the first level.
     */
    Level* getLevel(const std::string& levelName = "");

    /**
     * @brief Get the player.
     * @return The player.
     */
    Player* getPlayer() const;

    /**
     * @brief Load the game data, if not already loaded.
     * @return A handle to the starting level (the first level, if this is a new game, or the last level the player was in, if this was a loaded game)
     */
    Level* load();

	/**
	 * @brief A plot event occurred.
	 * @param event The plot event.
	 */
	virtual void plotOccurance(const PlotEvent& event);

    /**
     * @brief Save the current state of the game.
     * @param filename The filename to save to (leave blank to save to the previous filename)
     */
    void saveGame(const std::string& filename = "");


    private:
    /**
     * @brief Delete entities.
     */
    void mDeleteEntities();

    /**
     * @brief Retrieve the requested level.
     * @param levelName The name of the level to return.
     * @return The level data needed to create the level.
     */
    const LevelData& mFindLevel(const std::string& levelName);

    /**
     * @brief Get an entity by its name.
     * @param name The name of the entity.
     * @return The entity.
     */
    Entity* mGetEntity(const std::string& name);

    /**
     * @brief Retrieve an entity template.
     * @param keyword The template's keyword.
     * @return The template.
     *
     * @throws std::runtime_error Error thrown if template not found.
     */
    const EntityTemplate& mGetEntityTemplate(const std::string& keyword);

    /**
     * @brief Save the current level's state (in memory, don't save to a file until requested)
     */
    void mSaveLevelState();

    /**
     * The player.
     */
    Player* mPlayer;

    /**
     * The current level.
     */
    Level* mLevel;

    /**
     * The levels stored with their name as the keyword.
     */
    std::map<std::string, LevelData> mLevels;

	/**
	 * The entity templates.
	 */
    std::list<EntityTemplate> mEntityTemplates;

    /**
     * These are the loaded creatures.
     */
    std::list<Entity*> mLoadedEntities;
};

extern const std::string LEVEL_NULL;

#endif /* GAMEDATA_HPP_ */
