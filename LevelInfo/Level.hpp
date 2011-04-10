/*
 * Level.hpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */

#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <fstream>
#include <list>
#include <map>
#include <string>

#include "../Interfaces/ActionInterface.hpp"
#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../LevelInfo/ElipData.hpp"
#include "../Game/EnvironmentData.hpp"
#include "../Interfaces/EnvironmentInterface.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Game/Game.hpp"
#include "../Interfaces/GameInterfaceInterface.hpp"
#include "../Game/Input.hpp"
#include "../LevelInfo/LevelData.hpp"
#include "../MapInfo/Map.hpp"
#include "../Managers/MarkersManager.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../LevelInfo/QuadData.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief A level is a single contained area in the game.
 *
 * The level essentially acts as a manager between all objects (creatures, items, traps)
 * and a single map.  It is literally a solitary contained area in the game.
 */
class Level : public ActionInterface, public EnvironmentInterface, public EventInterface, public EventListener, public GameInterfaceInterface
{
    public:
    /**
     * @brief Construct a new level.
     * @param rule The map rule for the new level.
     * @param Difficulty The difficulty of the level to create.
     */
//    Level(const MapRule& rule, Difficulty difficulty); implement

    /**
     * @brief Construct a level from the saved string.
     * @param levelData The data needed to load a level.
     */
    Level(const LevelData& levelData);
    virtual ~Level();

    /**
     * @brief Add an entity to the level.
     * @param entity The entity to add.
     */
    virtual void addEntity(Entity* entity);

    /**
     * @brief Add a marker to the screen.
     * @param loc The location to add the marker.
     * @note should markers be here or in the GameScreen?
     */
    virtual void addMarker(const Vector& loc);

    /**
     * @brief Draw the map to the screen.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToVectorListener A potential moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creatureMovedToVectorListener = 0);

    /**
     * @brief Convert this level into it's base64 status.
     * @return The base64 data version of this level.
     */
    virtual std::string extractData() const;

    /**
     * @brief Get the name of this level.
     * @return The name of the level.
     */
    virtual const std::string& getName() const;

    /**
     * @brief Handle input.
     * @param event The input.
     */
    void handleInput(const Input& input);

    /**
     * @brief Called when the level has completed.
     * @param
     * @todo Need to implement a way of determining when the level is finished, what to do next (load the next level, quit the game, etc...), and passing information to a next level
     */
    virtual void levelFinished(bool next);

    /**
     * @brief Call any pre-logic level code.
     * @param playerPos The location at which the player enters the level.
     */
    virtual void load(const Vector& playerPos);

    /**
     * @brief Calling logic for a level will call logic for all map tiles (if necessary), creatures and objects.
     */
    virtual void logic();

    /**
     * @brief Remove an entity from the level.
     * @param name The name of the entity to remove.
     */
    virtual void removeEntity(const std::string& name);

    /**
     * @brief Unload the current level.
     */
    virtual void unload();

    private:
    /**
     * The name of the level.
     */
    std::string mName;

    /**
     * The initial points for the entities (as indicated by their IDs)
     */
    std::map<unsigned int, Vector> mInitialPositions;

    /**
     * A level has a map.
     */
    Map mMap;

    /**
     * This level's environment representation.
     */
    EnvironmentData mEData;

    /**
     * The marker's manager.
     */
    MarkersManager mMarkersManager;

    /**
     * The level-based lights.
     */
    std::list<QuadData> mLightsQuad;
    std::list<ElipData> mLightsElip;
};

#endif /* LEVEL_HPP_ */
