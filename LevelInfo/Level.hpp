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
#include "../Interfaces/EnvironmentInterface.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Game/Game.hpp"
#include "../Interfaces/GameInterfaceInterface.hpp"
#include "../Game/Input.hpp"
#include "../LevelInfo/LevelData.hpp"
#include "../Game/Map.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../LevelInfo/QuadData.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Vector.hpp"
#include "../Engine/Viewport.hpp"

class Entity;
class Player;

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
     * @param Difficulty The difficulty of the level to create.
     * @param player The player object.
     */
    Level(unsigned int difficulty, Player& player);
    virtual ~Level();

    /**
     * @brief Draw the map to the screen.
     * @param renderer The graphics object to draw with.
     * @param viewport The viewport within which to draw.
     */
    virtual void draw(Renderer& renderer, const Viewport& viewport);

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToVectorListener A potential moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creatureMovedToVectorListener = 0);

    /**
     * @brief Handle input.
     * @param event The input.
     */
    void handleInput(const Input& input);

    /**
     * @brief Called when the level has completed.
     * @todo Need to implement a way of determining when the level is finished, what to do next (load the next level, quit the game, etc...), and passing information to a next level
     */
    virtual void levelFinished(bool next);

    /**
     * Load the level.
     */
    virtual void load();

    /**
     * @brief Calling logic for a level will call logic for all map tiles (if necessary), creatures and objects.
     */
    virtual void logic();

    private:
    /**
     * The player handle.
     */
    Player* mPlayer;

    /**
     * The entities in the level.
     */
    std::list<Entity*> mEntities;

    /**
     * A level has a map.
     */
    Map mMap;

    /**
     * The level-based lights.
     */
    std::list<QuadData> mLightsQuad;
    std::list<ElipData> mLightsElip;
};

#endif /* LEVEL_HPP_ */
