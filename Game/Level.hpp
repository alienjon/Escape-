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
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/ChangeScoreListener.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Game/Game.hpp"
#include "../Game/Input.hpp"
#include "../Listeners/LevelCompleteListener.hpp"
#include "../Game/Map.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Vector.hpp"
#include "../Engine/Viewport.hpp"

class Entity;
class Player;
class Portal;

/**
 * @brief A level is a single contained area in the game.
 *
 * The level essentially acts as a manager between all objects (creatures, items, traps)
 * and a single map.  It is literally a solitary contained area in the game.
 */
class Level : public ActionInterface, public ChangeScoreInterface, public ChangeScoreListener, public DeathListener, public LevelCompleteListener, public gcn::Widget
{
    public:
    /**
     * @brief Construct a new level.
     * @param Difficulty The difficulty of the level to create.
     * @param player The player object.
     * @param viewport The screen's viewport.
     */
    Level(unsigned int difficulty, Player& player, Viewport& viewport);
    virtual ~Level();

	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change);

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
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    inline void deathOccurred(Entity* entity)
    {
    	mDeadEntities.push_back(entity);
    }

    /**
     * @brief Draw, from gcn::Widget
     * @param graphics The graphics object.
     */
    virtual void draw(gcn::Graphics* graphics)
    {}

    /**
     * @brief Draw the map to the screen.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Return the level's entrance/exit area.
     * @return The entrance/exit area of this map.
     */
    const Vector& getPortal() const;

    /**
     * @brief Get the map.
     * @return The map.
     */
    const Map& getMap() const;

    /**
     * @brief Returns the viewport.
     * @return The level's viewport.
     */
    const Viewport& getViewport() const;

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
     * @brief A level complete signal is called.
     */
    virtual void levelComplete();

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
     * @brief Add an entity to the level.
     * @param entity The entity to add.
     */
    void mAddEntity(Entity* entity);

    /**
     * @brief Remove an entity to the level.
     * @param entity The entity to remove.
     */
    void mRemoveEntity(Entity* entity);

    /**
     * True if the level has completed.
     */
    bool mIsDone;

    // The player handle.
    Player* mPlayer;

    Portal* mPortal;

    // The entities in the level.
    std::list<Entity*> mEntities;

    // A level has a map.
    Map mMap;

    // The viewport for this level.
    Viewport& mViewport;

    // The listeners.
    std::list<Entity*> mDeadEntities;
};

#endif /* LEVEL_HPP_ */
