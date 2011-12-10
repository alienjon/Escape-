/*
 * Level.hpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <list>

#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

#include "../Interfaces/ActionInterface.hpp"
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/ChangeScoreListener.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Listeners/FloatingTextListener.hpp"
#include "../Interfaces/GCNActionInterface.hpp"
#include "../Listeners/LevelCompleteListener.hpp"
#include "../Game/Map.hpp"
#include "../Entities/Portal.hpp"
#include "../Interfaces/TimeChangeInterface.hpp"
#include "../Listeners/TimeChangeListener.hpp"
#include "../Engine/Timer.hpp"

class Creature;
class Entity;
class Player;

/**
 * @brief A level is a single contained area in the game.
 *
 * The level essentially acts as a manager between all objects (creatures, items, traps)
 * and a single map.  It is literally a solitary contained area in the game.
 */
class Level : public ActionInterface, public ChangeScoreInterface, public ChangeScoreListener, public DeathListener, public GCNActionInterface,
			  public FloatingTextListener, public LevelCompleteListener, public TimeChangeInterface, public TimeChangeListener
{
    public:
    /**
     * @brief Construct a new level.
     * @param difficulty The difficulty of the level to create.
     */
    Level(unsigned int difficulty, Player& player);
    virtual ~Level();

    /**
     * @brief Display a floating text on the screen for a short period of time.
     * @param str The text to display.
     * @param position The initial position to display the text (it will float up over a short period of time)
     * @param color The color of the text to display.
     * @param size The character size of the text.
     */
    virtual void addFloatingText(const std::string& str, const sf::Vector2f& position, const sf::Color& color, unsigned int size);

	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change);

    /**
     * @brief Check if the provided entity collides with anything in the map and, if so, collide them.
     * @param entity The entity to check collisions against.
     * @return Returns true if a collision occurred where both entities are collidable - meaning that they cannot move through each other.
     */
    bool checkEntityCollision(Entity& entity);

    /**
     * @brief Check if the provided entity collides with the map.
     * @param entity The entity to check collisions against.
     * @return True if a collision was found.
     */
    bool checkMapCollision(Entity& entity);

    /**
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    inline void deathOccurred(Entity* entity)
    {
    	mDeadEntities.push_back(entity);
    }

    /**
     * @brief Draw the map to the screen.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(gcn::SFMLGraphics& renderer);

    /**
     * @brief Flip the level upside-down.
     */
    virtual void flip();

    /**
     * @brief Get the map.
     * @return The map.
     */
    const Map& getMap() const;

    /**
     * @brief Checks whether the level has completed.
     * @return True if the level has completed.
     */
    bool isDone() const;

    /**
     * @brief A level complete signal is called.
     */
    virtual void levelComplete();

    /**
     * @brief Calling logic for a level will call logic for all map tiles (if necessary), creatures and objects.
     * @param camera The camera that is looking at the level.
     */
    virtual void logic(sf::View& camera);

    /**
     * @brief Phase move the creature.
     * @param creature The creature to phase.
     * @note If the creature is a player show a widget to have the player select a phase direction.
     */
    void phaseCreature(Creature& creature);

    /**
     * @brief Tell any creatures waiting to phase the direction to do so.
     * @param dir The direction to phase.
     */
    void phaseDirection(const std::string& dir);

    /**
     * @brief Called when the player finds the exit.
     */
    void playerFoundExit();

    /**
     * @brief Teleport the player to a random position within the map.
     * @note As the keys are definitely in the corners, the player will be at least 1 cell in on all sides.
     */
    void teleportPlayer();

    /**
     * @brief Distribute a time change event.
     * @param time The time to change.
     */
    virtual void timeChange(int time)
    {
    	distributeTimeChange(time);
    }

    /**
     * @brief Zoom the level.
     */
    virtual void zoom();

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

    // True if the level has completed.
    bool mIsDone;

    // The player handle.
    Player& mPlayer;

    // The portal.
    Portal mPortal;

    // The entities in the level.
    std::list<Entity*> mEntities;

    // These are the floating texts found in the level.
    std::list<sf::Text> mFloatingTexts;

    // This is the floating text timer.
    Timer mFloatingTextTimer;

    // A level has a map.
    Map mMap;

    // Lists of things the levle manages.
    std::list<Entity*> mDeadEntities;
    std::list<Creature*> mPhaseList;

    // A list of pickups that could still be picked up and a toggle to check if an award has been given for picking all items up.
    std::list<Entity*> mPickups;
    bool mPickupAward;

    // Flipping data.
    Timer mFlipTimer;
    float mFlipAngle;
    bool mFlipped;

    // Zooming data.
    Timer mZoomTimer;
    float mZoomFactor;
    bool mZoomed;

    // Teleporter information.
    Timer mTeleportTimer;
    unsigned int mTeleportInterval,
				 mTeleportIntervalMin,
				 mTeleportIntervalMax;
};

#endif /* LEVEL_HPP_ */
