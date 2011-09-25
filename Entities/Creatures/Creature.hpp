/*
 * Creature.hpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include <list>

#include "../../Managers/AnimationManager.hpp"
#include "../../Entities/Creatures/CreatureAnimationState.hpp"
#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Listeners/DeathListener.hpp"
#include "../../Entities/Entity.hpp"
#include "../../Entities/Templates/EntityTemplate.hpp"
#include "../../Math/Vector.hpp"
#include "../../Math/Quadrilateral.hpp"
#include "../../Engine/Timer.hpp"

class Item;

/**
 * @brief A base class for all creatures.
 */
class Creature : public DeathListener, public Entity
{
	friend class DisplayCreatureAnimationAction;

    public:
    /**
     * @brief Construct a creature based on the provided creature-specific data and generic template.
     * @param name The creature's name.
     * @param tmpl The template information from which the creature is based.
     * @param alig The creature's alignment.
     * @param health The creature's maximum health.
     * @param defense The creature's maximum defense.
     */
    Creature(const std::string& name, const EntityTemplate& temp, const std::string& alig, unsigned int health, unsigned int defense);

    /**
     * @brief Construct a previously constructed creature based on provided data.
     * @param data The data which can be used to generate a new creature.
     */
    Creature(const std::string& data);
    virtual ~Creature();

    /**
     * @brief Add a moved to point listener.
     * @param listener The listener to add.
     */
    void addCreatureMovedToPointListener(CreatureMovedToPointListener* listener);

    /**
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    virtual void deathOccurred(Entity& entity);

    /**
     * @brief Drop an item.
     * @param name The name of the item to drop.
     * @return The item to be dropped, or null if not being held.
     */
    virtual Item* dropItem(const std::string& name);

    /**
     * @brief Get the currently facing direction.
     * @return The currently facing direction.
     */
    virtual Direction getFacingDirection() const;

    /**
     * @brief Get the point being looked at.
     * @return The point the creature is looking at.
     */
    virtual const Vector& getFacingVector() const;

    /**
     * @brief Get the current speed of the creature.
     */
    virtual double getSpeed() const;

    /**
     * @brief Checks if the creature is currently searching.
     * @return True if the creature is searching.
     */
    bool isSearching() const;

    /**
     * @brief Checks if the creature is wandering.
     * @return The state of this creature's wandering behavior.
     */
    bool isWandering() const;

    /**
     * @brief Kill the creature.
     */
    virtual void kill();

    /**
     * @brief Perform internal logic.
     * @param eData The level environment in which this entity resides.
     */
//    virtual void logic(EnvironmentData& eData);@todo review

    /**
     * @brief Look at the provided point.
     * @param point The point to look at.
     */
    virtual void lookAt(const Vector& point);

    /**
     * @brief Move to the requested point.
     * @param x The x position to move.
     * @param y The y position to move.
     */
    virtual void moveTo(int x, int y);

    /**
     * @brief Pick up an item.
     * @param item The item to pick up.
     */
    virtual void pickupItem(Item& item);

    /**
     * @brief Remove a moved to point listener.
     * @param listener The listener to add.
     */
    void removeCreatureMovedToPointListener(CreatureMovedToPointListener* listener);

    /**
     * @brief Set the search area.
     * @param span The search span.
     * @param distance The search distance.
     */
    void setSearchArea(unsigned int span, unsigned int distance);

    /**
     * @brief Set to true to have this creature look for other entities.
     * @param state True to enable searching.
     */
    void setSearching(bool state);

    /**
     * @brief Set the speed of this creature when it moves.
     * @param speed The speed to set.
     * @note The speed is a double value between 0.0 and 1.0.  Higher/Lower numbers will be capped.
     */
    virtual void setSpeed(double speed);

    /**
     * @brief Set the wandering state of the creature.
     * @param state The wandering state of the creature.
     */
    void setWandering(bool state);

    /**
     * @brief Stop all movement.
     */
    virtual void stop();

    /**
     * @brief Tell the creature to wander.
     */
    virtual void wander();

    protected:
    /**
     * The length of time (in ms) an enemy will wait if it is wandering.
     */
    static const int WANDER_PAUSE_TIME;

    /**
     * The pause time for a creature between movements.
     */
    static const int CREATURE_PAUSE_TIME_BETWEEN_MOVEMENTS;

    /**
     * @brief This entity collided with the collidee
     * @param collidee The entity that has collided with this entity.
     */
    virtual void mCollision(Entity& collidee);

    /**
     * @brief Virtual function to have creature derivitives interact with an interacting object..
     * @param object The object to interact with.
     */
    virtual void mCreatureInteract(Entity* object) // @todo check this!
    {}

    /**
     * @brief Stuff to do when the creature dies.
     */
    virtual void mDie();

    /**
     * @brief Retrieve the creature animation keyword based on the currently facing direction.
     * @param animation The animation to retrieve.
     * @return The keyword.
     */
    const std::string& mGetAnimationKeyword(CreatureAnimationState animation);

    /**
     * @brief Create an area that is right in front of the creature.
     * @param span The distance in front of the creature to reach.
     * @param xOffset The x offset.
     * @param yOffset The y offset.
     * @return An area immediately in front of the creature.
     * @note Used for interactions.
     */
    Quadrilateral mGetAreaInFront(unsigned int span, int xOffset, int yOffset) const;

    /**
     * @brief Load the animations for this entity.
     * @param prefix This is essentially the entity keyword to prefix to the animations.
     */
    virtual void mLoadAnimations(const std::string& prefix);

    /**
     * @brief Tell the moved to point listeners that the creature has finished moving to the next point.
     */
    void mMovedToVector();

    /**
     * @brief Set the current animation.
     * @param animation The animation.
     */
    virtual void mSetAnimation(CreatureAnimationState animation);

    /**
     * @brief When a creature is told to stop() it ceases all movement.  A soft stop allows for a pause
     * 		  between movements (like when a creature has moved to a point)
     */
    void mSoftStop();

    /**
     * The direction the creature is currently moving.
     */
    Direction mFacingDirection;

    /**
     * The X and Y velocity of the creature.
     */
    double mXVelocity,
		   mYVelocity;

    /**
     * The point the creature is currently moving towards.
     */
    Vector mWaypoint;

    /**
     * The listener lists.
     */
    std::list<CreatureMovedToPointListener*> mMovedToPointListeners;

    /**
     * Currently held items.
     */
    std::list<Item*> mHeldItems;

    /**
     * These are the animation names for the various creature animations.
     * All creatures must have an animation for all of these.
     */
    std::string mWalkingUp, mWalkingUpRight, mWalkingRight, mWalkingDownRight, mWalkingDown, mWalkingDownLeft, mWalkingLeft, mWalkingUpLeft,
				mStandingUp, mStandingUpRight, mStandingRight, mStandingDownRight, mStandingDown, mStandingDownLeft, mStandingLeft, mStandingUpLeft,
				mHurtUp, mHurtUpRight, mHurtRight, mHurtDownRight, mHurtDown, mHurtDownLeft, mHurtLeft, mHurtUpLeft,
				mFallingUp, mFallingUpRight, mFallingRight, mFallingDownRight, mFallingDown, mFallingDownLeft, mFallingLeft, mFallingUpLeft;

	/**
	 * Vector being looked at.
	 */
	Vector mLookingAt;

	/**
	 * This is the current victim.
	 */
	Entity* mVictim;

    private:
    /**
     * The speed at which this creature is moving. (1.0 is 100% speed, but higher is faster, etc...)
     */
    double mSpeed;

    /**
     * True if the creature is moving.
     */
    Timer mMovementTimer;

    /**
     * True if the creature is searching.
     */
    bool mIsSearching;

    /**
     * True if the creature is wandering.
     */
    bool mIsWandering;

    /**
     * The creature's visible search area.
     */
    unsigned int mSearchSpan,
				 mSearchDistance;

    /**
     * The attack timer.
     */
    Timer mAttackTimer;

    /**
     * The current creature animation state.
     */
    CreatureAnimationState mCreatureAnimationState;
};

#endif
