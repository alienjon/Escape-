/*
 * Creature.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Creature.hpp"

#include "../Actions/AlphaCycleAction.hpp"
#include "../Actions/CheckCollisionAction.hpp"
#include "../Game/Level.hpp"
#include "../Actions/MoveToAction.hpp"
#include "../Actions/MultipleActionsAction.hpp"
#include "../Actions/SetCollidableAction.hpp"
#include "../Actions/SetInteractableAction.hpp"

using std::list;
using std::queue;

const unsigned int CREATURE_MOVEMENT_DISTANCE = 4;

Creature::Creature() :
	mUp(false), mDown(false), mLeft(false), mRight(false),
	mSpeed(1.f),
	mMovable(true)
{
	mType = ENTITY_CREATURE;
    mMovementTimer.start();
}

Creature::~Creature()
{
    // Need to delete the actions here, because if I wait until the creature is deleted, certain
    // objects that are part of an entity (or other sub-classes) may get removed while still
    // needing the creature-like aspects of this object {cough cough moveToAction() cough cough}
    clearActions();
}

void Creature::mDie()
{
    // Stop moving.
    setMovable(false);

    // Continue dying.
    Entity::mDie();
}

void Creature::mMovedToWaypoint()
{
    // Tell all listeners that the creature has moved to the next path point.
    for(list<CreatureWaypointListener*>::iterator it = mWaypointListeners.begin(); it != mWaypointListeners.end(); it++)
        (*it)->creatureMoved(*this);
}

void Creature::logic(Level& level)
{
	// If the creature is moving towards a waypoint, determine the direction to move.
	if(!mWaypoints.empty())
	{
		mUp = mDown = mLeft = mRight = false;
		if(mWaypoints.front().y < getY() - CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mUp = true;
		if(mWaypoints.front().y > getY() + CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mDown = true;
		if(mWaypoints.front().x < getX() - CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mLeft = true;
		if(mWaypoints.front().x > getX() + CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mRight = true;
	}

	// If the creature is moving in at least one direction then move.
	if(isMovable() && (mUp || mDown || mLeft || mRight))
	{
		// If we're moving, then do the generic stuff.
		if(mMovementTimer.getTime() > 5)
		{
			float dist = CREATURE_MOVEMENT_DISTANCE * mSpeed;
			if(mUp)
			{
				setY(getY() - dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setY(getY() + dist);
				if(entity && !mWaypoints.empty())
					mUp = false;
			}
			if(mDown)
			{
				setY(getY() + dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setY(getY() - dist);
				if(entity && !mWaypoints.empty())
					mDown = false;
			}
			if(mLeft)
			{
				setX(getX() - dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setX(getX() + dist);
				if(entity && !mWaypoints.empty())
					mLeft = false;
			}
			if(mRight)
			{
				setX(getX() + dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setX(getX() - dist);
				if(entity && !mWaypoints.empty())
					mRight = false;
			}

			// Restart the timer.
			mMovementTimer.start();
		}
	}

	// If the creature is moving to a waypoint and all directions have stopped moving, go to the next waypoint.
	if(!mWaypoints.empty() && (!mUp && !mDown && !mLeft && !mRight))
	{
		mWaypoints.pop();
		mMovedToWaypoint();
	}

    // Call the entity's logic.
    Entity::logic(level);
}

void Creature::phaseTo(const sf::Vector2f& vec)
{
	// Create the action list of what is to be done for phasing.
	ActionList* lst = new ActionList();

	// Start oscillating the player alpha.
	AlphaCycleAction* alpha = new AlphaCycleAction(*this);
	addCreatureWaypointListener(alpha);
	lst->push_back(alpha);

	// Check the collidable and interactable states and set as appropriate (they need to be false for the phase walk, but set it back afterwards)
	if(isCollidable())
		lst->push_back(new SetCollidableAction(*this, false));
	if(isInteractable())
		lst->push_back(new SetInteractableAction(*this, false));
	lst->push_back(new MoveToAction(*this, vec));

	// Combine the actions together in a multiple action.
	addAction(new MultipleActionsAction(lst));

	// Create the action list of what is to be done to cleanup from phasing.
	lst = new ActionList();
	if(isCollidable())
		lst->push_back(new SetCollidableAction(*this, true));
	if(isInteractable())
		lst->push_back(new SetInteractableAction(*this, true));
	addAction(new MultipleActionsAction(lst));

	// After all the rest of this, check to see if the creature landed on something.
	addAction(new CheckCollisionAction(*this));
}

void Creature::setWaypoint(const sf::Vector2f& waypoint)
{
	while(!mWaypoints.empty())
		mWaypoints.pop();
	addWaypoint(waypoint);
}

void Creature::stop()
{
    // Stop all movements.
	mUp = mDown = mLeft = mRight = false;

    // Consider the creature to have moved to its next waypoint.
	while(!mWaypoints.empty())
		mWaypoints.pop();
    mMovedToWaypoint();

	// Also stop doing stuff.
	clearActions();
}
