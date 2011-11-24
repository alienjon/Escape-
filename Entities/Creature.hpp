/*
 * Creature.hpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef CREATURE_HPP_
#define CREATURE_HPP_

//#include <list>
//
//#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Entities/Entity.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief A base class for all creatures.
 */
class Creature : public Entity
{
    public:
    virtual ~Creature();

//    /**
//     * @brief Add a moved to point listener.
//     * @param listener The listener to add.
//     */
//    inline void addCreatureMovedToPointListener(CreatureMovedToPointListener* listener)
//    {
//        mMovedToPointListeners.push_back(listener);
//    }

    /**
     * @brief Get the current speed of the creature.
     * @return The speed of the creature.
     */
    inline double getSpeed() const
    {
        return mSpeed;
    }

    /**
     * @brief Perform internal logic.
     * @param level The level within which the creature is residing.
     */
    virtual void logic(Level& level);

//    /**
//     * @brief Move to the requested point.
//     * @param x The x position to move.
//     * @param y The y position to move.
//     */
//    virtual void moveTo(int x, int y);
//
//    /**
//     * @brief Remove a moved to point listener.
//     * @param listener The listener to add.
//     */
//    inline void removeCreatureMovedToPointListener(CreatureMovedToPointListener* listener)
//    {
//        mMovedToPointListeners.remove(listener);
//    }

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
     * @brief Stop all movement.
     */
    virtual void stop();

//    /**
//     * @brief Tell the creature to wander.
//     */
//    virtual void wander();
//
//    protected:
//    /**
//     * The length of time (in ms) an enemy will wait if it is wandering.
//     */
//    static const int WANDER_PAUSE_TIME;
//
//    /**
//     * The pause time for a creature between movements.
//     */
//    static const int CREATURE_PAUSE_TIME_BETWEEN_MOVEMENTS;

    /**
     * @brief Construct a creature.
     */
    Creature();

    /**
     * @brief Stuff to do when the creature dies.
     */
    virtual void mDie();

//    /**
//     * @brief Tell the moved to point listeners that the creature has finished moving to the next point.
//     */
//    void mMovedToVector();

    /**
     * @brief When a creature is told to stop() it ceases all movement.  A soft stop allows for a pause
     * 		  between movements (like when a creature has moved to a point)
     */
    void mSoftStop();

    // The four directionals.
    bool mUp, mDown, mLeft, mRight;

//    /**
//     * The point the creature is currently moving towards.
//     */
//    Vector mWaypoint;
//
//    /**
//     * The listener lists.
//     */
//    std::list<CreatureMovedToPointListener*> mMovedToPointListeners;

    private:
    // The speed at which this creature is moving. (1.0 is 100% speed, but higher is faster, etc...)
    double mSpeed;

    // True if the creature is moving.
    Timer mMovementTimer;
};

#endif
