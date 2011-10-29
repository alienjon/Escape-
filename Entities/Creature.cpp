/*
 * Creature.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Creature.hpp"

#include <set>
#include <stdexcept>

#include "../Game/Level.hpp"
#include "../main.hpp"
#include "../Actions/MoveToAction.hpp"
#include "../Actions/MultipleActionsAction.hpp"
#include "../Actions/PauseAction.hpp"
#include "../Actions/WanderAction.hpp"

using std::list;
using std::runtime_error;
using std::set;
using std::string;

const unsigned int CREATURE_MOVEMENT_DISTANCE = 4;

Creature::Creature() :
	mXVelocity(0),
	mYVelocity(0),
	mSpeed(1.0)
{
	// This is a creature.
	mType = ENTITY_CREATURE;

    // Start the timers.
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
	// Stop doing stuff.
	stop();
	mMovementTimer.stop();

	// Finish killing the creature.
	Entity::mDie();
}

void Creature::mMovedToVector()
{
    // Tell all listeners that the creature has moved to the next path point.
    for(list<CreatureMovedToPointListener*>::iterator it = mMovedToPointListeners.begin(); it != mMovedToPointListeners.end(); it++)
    {
        // Tell the listener the point was moved to.
        (*it)->creatureMoved(*this);
    }
}

void Creature::mSoftStop()
{
    // Stop all movements.
    mXVelocity = mYVelocity = 0;

    // Consider the creature to have moved to it's point.
    mMovedToVector();
}

void Creature::logic(Level& level)
{
	// If the creature is moving in at least one direction and there arne't any creatures holding this one, then move.
	if((mXVelocity != 0 || mYVelocity != 0))
	{
		bool xCollide = false,
			 yCollide = false;

		// If the non-player creature has moved within range of the waypoint, then set to that waypoint's position.
		if(getType() != ENTITY_PLAYER)
		{
			// If the creature has moved to the correct X axis point (or within +- mSpeed range) then stop movement on the X axis.
			if(mXVelocity && (getX() >= mWaypoint.x - CREATURE_MOVEMENT_DISTANCE && getX() <= mWaypoint.x + CREATURE_MOVEMENT_DISTANCE))
			{
				mXVelocity = 0;
				setX(mWaypoint.x);
			}

			// If the creature has moved to the correct Y axis point (or within +- mSpeed range) then stop movement on the Y axis.
			if(mYVelocity && (getY() >= mWaypoint.y - CREATURE_MOVEMENT_DISTANCE && getY() <= mWaypoint.y + CREATURE_MOVEMENT_DISTANCE))
			{
				mYVelocity = 0;
				setY(mWaypoint.y);
			}
		}

		// If we're moving, then do the generic stuff.
		if(mMovementTimer.getTime() > (25 - (getSpeed() * 10)))
		{
			// Restart the timer.
			mMovementTimer.start();

			// Now do generic movement stuff.
			if(mXVelocity)
			{
				// Update the X position and check for a collision.
				setX(getX() + (mXVelocity * CREATURE_MOVEMENT_DISTANCE));
				Entity* x_entity = level.checkEntityCollision(*this);
				bool x_wall = level.checkMapCollision(*this);
				if(x_wall || x_entity)
				{
					// Return to the previous X position if both this creature and the collision entity are collidable.
					if(x_wall || (isCollidable() && x_entity->isCollidable()))
						setX(getX() - (mXVelocity * CREATURE_MOVEMENT_DISTANCE));

					// Hit the X side.
					xCollide = true;

					// If an entity was found and it is interactable, collide with it.
					if(isInteractable() && x_entity && x_entity->isInteractable())
						x_entity->collide(*this);
				}
			}
			if(mYVelocity)
			{
				// Update the Y position and check for a collision.
				setY(getY() + (mYVelocity * CREATURE_MOVEMENT_DISTANCE));
				Entity* y_entity = level.checkEntityCollision(*this);
				bool y_wall = level.checkMapCollision(*this);
				if(y_wall || y_entity)
				{
					// Return to the previous Y position.
					if(y_wall || (isCollidable() && y_entity->isCollidable()))
						setY(getY() - (mYVelocity * CREATURE_MOVEMENT_DISTANCE));

					// Hit the Y side.
					yCollide = true;

					// If an entity was found and it is interactable, collide with it.
					if(isInteractable() && y_entity && y_entity->isInteractable())
						y_entity->collide(*this);
				}
			}

			// If both x and y collisions have occurred (and this is NOT the player) then consider this to be a corner.
			// @todo I might be able to separate this code into a more defined 'NPC' class that focuses on movement logic.
			//		 What I might want to do is that if an NPC hits an X or Y collision, to then move left or right until
			//		 the NPC can continue moving the the original direction.  If that NPC then hits a collision on the
			//		 other axis to switch directions on the second axis.  If a second collision then occurs, then the
			//		 creature should stop.
			if((xCollide && yCollide) && getType() != ENTITY_PLAYER)
			{
				mSoftStop();
			}
		}

		// If the creature was moving at the beginning of this logic call but isn't now, then it has stopped.
		if(mXVelocity == 0 && mYVelocity == 0)
		{
			mSoftStop();
		}
	}

    // Call the entity's logic.
    Entity::logic(level);
}

void Creature::moveTo(int x, int y)
{
    // Set the waypoint.
    mWaypoint.x = x;
    mWaypoint.y = y;

    // Update the velocities.
	mXVelocity = (getX() < x) ? 1 : ((getX() == x) ? 0 : -1);
	mYVelocity = (getY() < y) ? 1 : ((getY() == y) ? 0 : -1);
}

void Creature::stop()
{
	// Do a regular soft stop first.
	mSoftStop();

	// Stop wandering.
//	setWandering(false);@todo review

	// Also stop doing stuff.
	clearActions();
}

void Creature::wander()
{
    // Pick a number.  If 0-7 is selected, move a random distance in a random direction.  Otherwise, pause for a bit.
    int xDist = 50 * random(1,2);
    int yDist = 50 * random(1,2);

    // The 8 directions (0-7) plus an additional for waiting around a bit.
    switch(random(0, 20))
    {
        case 0: // Move up.
        {
            addAction(new MoveToAction(*this, Vector(getX(), getY() - yDist)));
            break;
        }
        case 1: // Move upright.
        {
            addAction(new MoveToAction(*this, Vector(getX() + xDist, getY() - yDist)));
            break;
        }
        case 2: // Move right.
        {
            addAction(new MoveToAction(*this, Vector(getX() + xDist, getY())));
            break;
        }
        case 3: // Move downright.
        {
            addAction(new MoveToAction(*this, Vector(getX() + xDist, getY() + yDist)));
            break;
        }
        case 4: // Move down.
        {
            addAction(new MoveToAction(*this, Vector(getX(), getY() + yDist)));
            break;
        }
        case 5: // Move downleft.
        {
            addAction(new MoveToAction(*this, Vector(getX() - xDist, getY() + yDist)));
            break;
        }
        case 6: // Move left.
        {
            addAction(new MoveToAction(*this, Vector(getX() - xDist, getY())));
            break;
        }
        case 7: // Move upleft.
        {
            addAction(new MoveToAction(*this, Vector(getX() - xDist, getY() - yDist)));
            break;
        }
        default:
        {
            addAction(new PauseAction(random((WANDER_PAUSE_TIME / 2), (WANDER_PAUSE_TIME * 2))));
        }
    }

    // If we're wandering, continue wandering afterwards.
//    if(isWandering())//@todo review
//    {
//        addAction(new WanderAction(this));
//    }
}

const int Creature::WANDER_PAUSE_TIME = 4000;

const int Creature::CREATURE_PAUSE_TIME_BETWEEN_MOVEMENTS = 2500;
