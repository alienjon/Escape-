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
class GameScreen;
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
     * @param parent The parent gamescreen.
     */
    Level(unsigned int difficulty, Player& player, GameScreen* parent);
    virtual ~Level();

    /**
     * @brief Check if the provided entity collides with anything in the map.
     * @param entity The entity to check collisions against.
     * @return The entity that was collided against, or null if no collisions detected.
     */
    virtual Entity* checkEntityCollision(const Entity& entity) const;

    /**
     * @brief Check if the provided entity collides with the map.
     * @param entity The entity to check collisions against.
     * @return True if a collision was found.
     */
    virtual bool checkMapCollision(const Entity& entity) const;

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
     * @brief Return the exit area.
     * @return The exit area of this map.
     */
    const Rectangle& getExitArea() const;

    /**
     * @brief Return the viewport's offset.
     * @return The viewport offset.
     */
    const Vector getViewportOffset() const;

    /**
     * @brief Handle input.
     * @param event The input.
     */
    void handleInput(const Input& input);

    /**
     * @brief Checks whether the level has completed.
     * @return True if the level has completed.
     */
    virtual bool isDone() const;

    /**
     * @brief Calling logic for a level will call logic for all map tiles (if necessary), creatures and objects.
     */
    virtual void logic();

    /**
     * @brief Called when the player finds the exit.
     */
    virtual void playerFoundExit();

    private:
    /**
     * True if the level has completed.
     */
    bool mIsDone;

    /**
     * The viewport for this level.
     */
    Viewport mViewport;

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

    /**
     * The parent gamescreen.
     */
    GameScreen* mGameScreen;
};

#endif /* LEVEL_HPP_ */
