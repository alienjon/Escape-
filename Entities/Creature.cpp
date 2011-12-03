/*
 * Creature.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Creature.hpp"

#include "../Game/Level.hpp"

using std::list;
using std::queue;

const unsigned int CREATURE_MOVEMENT_DISTANCE = 4;

Creature::Creature() :
	mUp(false), mDown(false), mLeft(false), mRight(false),
	mSpeed(1.f)
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
	if(mUp || mDown || mLeft || mRight)
	{
		// If we're moving, then do the generic stuff.
		if(mMovementTimer.getTime() > 5)
		{
			float dist = CREATURE_MOVEMENT_DISTANCE * mSpeed;
			if(mUp)
			{
				setY(getY() - dist);
				bool wall	= level.checkMapCollision(*this),
					 entity = level.checkEntityCollision(*this);
				if(wall || entity)
					setY(getY() + dist);
				if(entity && !mWaypoints.empty())
					mUp = false;
			}
			if(mDown)
			{
				setY(getY() + dist);
				bool wall	= level.checkMapCollision(*this),
					 entity = level.checkEntityCollision(*this);
				if(wall || entity)
					setY(getY() - dist);
				if(entity && !mWaypoints.empty())
					mDown = false;
			}
			if(mLeft)
			{
				setX(getX() - dist);
				bool wall	= level.checkMapCollision(*this),
					 entity = level.checkEntityCollision(*this);
				if(wall || entity)
					setX(getX() + dist);
				if(entity && !mWaypoints.empty())
					mLeft = false;
			}
			if(mRight)
			{
				setX(getX() + dist);
				bool wall	= level.checkMapCollision(*this),
					 entity = level.checkEntityCollision(*this);
				if(wall || entity)
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
