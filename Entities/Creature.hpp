/*
 * Creature.hpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include <list>
#include <queue>
#include <string>

#include <SFML/System.hpp>

#include "../Listeners/CreatureWaypointListener.hpp"
#include "../Entities/Entity.hpp"
#include "../Listeners/PhaseMovementListener.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief A base class for all creatures.
 */
class Creature : public Entity, public PhaseMovementListener
{
    public:
    virtual ~Creature();

    /**
     * @brief Add a moved to point listener.
     * @param listener The listener to add.
     */
    inline void addCreatureWaypointListener(CreatureWaypointListener* listener)
    {
    	mWaypointListeners.push_back(listener);
    }

    /**
     * @brief Add a waypoint for the creature to move toward.
     * @param waypoint The location on the map for the player to move.
     */
    inline void addWaypoint(const sf::Vector2f& waypoint)
    {
    	mWaypoints.push(waypoint);
    }

    /**
     * @brief Get the current speed of the creature.
     * @return The speed of the creature in pixels per second.
     */
    inline double getSpeed() const
    {
        return mSpeed;
    }

    /**
     * @brief Is this creature able to move right now?
     * @return True if the creature is able to move.
     */
    inline bool isMovable() const
    {
    	return mMovable;
    }

    /**
     * @brief Perform internal logic.
     * @param level The level within which the creature is residing.
     * @param delta The time since the last frame displayed.
     */
    virtual void logic(Level& level, int delta);

    /**
     * @brief Phase this creature to the specified position.
     * @param vec The position to phase the creature to.
     */
    virtual void phaseTo(const sf::Vector2f& vec);

    /**
     * @brief Remove a moved to point listener.
     * @param listener The listener to add.
     */
    inline void removeCreatureWaypointListener(CreatureWaypointListener* listener)
    {
        mWaypointListeners.remove(listener);
    }

    /**
     * @brief Set the movable state of the creature.
     * @param state The state to set.
     */
    inline void setMovable(bool state)
    {
    	mMovable = state;
    }

    /**
     * @brief Set the speed of this creature when it moves.
     * @param speed The speed to set.
     * @note The speed is a double value between 0.0 and 1.0.  Higher/Lower numbers will be capped.
     */
    inline void setSpeed(double speed)
    {
        mSpeed = (speed < 0.0) ? 0.0 : speed;
    }

    /**
     * @brief Set the current waypoint.
     * @param waypoint The waypoint to set.
     * @note Calling this function clears all waypoints and then sets the provided waypoint as the next one.
     */
    virtual void setWaypoint(const sf::Vector2f& waypoint);

    /**
     * @brief Stop all movement.
     * @note This clears all waypoints.
     */
    virtual void stop();

    protected:
    /**
     * @brief Construct a creature.
     * @param imageData The image data with which to create the creature's display.
     */
    Creature(const std::string& imageData);

	/**
	 * @brief The creature has died.
	 */
	virtual void mDie();

    /**
     * @brief Tell the moved to point listeners that the creature has finished moving to the next point.
     */
    void mMovedToWaypoint();

    /**
     * @brief Update the facing direction animation.
     */
    void mUpdateFacingAnimation();

    // The four directionals.
    bool mUp, mDown, mLeft, mRight;

    private:
    // The speed at which this creature is moving. (1.0 is 100% speed, but higher is faster, etc...)
    double mSpeed, mCurrentSpeed;

    // True if the creature is moving.
    Timer mMovementTimer;

    // The queue of waypoints.
    std::queue<sf::Vector2f> mWaypoints;

    // The waypoint listeners.
    std::list<CreatureWaypointListener*> mWaypointListeners;

    // The movability state.
    bool mMovable;

    // The 9 facing directions.
    typedef enum
    {
    	FACINGDIRECTION_NEUTRAL = 0,
    	FACINGDIRECTION_UP = 1,
    	FACINGDIRECTION_UPRIGHT = 2,
    	FACINGDIRECTION_RIGHT = 3,
    	FACINGDIRECTION_DOWNRIGHT = 4,
    	FACINGDIRECTION_DOWN = 5,
    	FACINGDIRECTION_DOWNLEFT = 6,
    	FACINGDIRECTION_LEFT = 7,
    	FACINGDIRECTION_UPLEFT = 8,
    	FACINGDIRECTION_INVALID
    } FacingDirection;
    std::vector<AnimatedSprite> mDirections;
};

#endif
