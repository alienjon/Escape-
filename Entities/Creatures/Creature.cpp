/*
 * Creature.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Creature.hpp"

#include <set>
#include <stdexcept>

#include "../../Managers/AnimationManager.hpp"
#include "../../Entities/Non-Creatures/Item.hpp"
#include "../../Actions/DisplayCreatureAnimationAction.hpp"
#include "../../Game/Keywords.hpp"
#include "../../LevelInfo/Level.hpp"
#include "../../main.hpp"
#include "../../Actions/MoveToAction.hpp"
#include "../../Actions/MultipleActionsAction.hpp"
#include "../../Actions/PauseAction.hpp"
#include "../../Actions/PlaySoundAction.hpp"
#include "../../Actions/SetSearchingAction.hpp"
#include "../../Managers/VideoManager.hpp"
#include "../../Actions/WanderAction.hpp"

using std::list;
using std::runtime_error;
using std::set;
using std::string;

const unsigned int CREATURE_MOVEMENT_DISTANCE = 2;

const unsigned int CREATURE_ATTACK_INTERVAL = 1000;

const string CREATURE_KEYWORD_WALKING_UP = "_WALKING_UP";
const string CREATURE_KEYWORD_WALKING_UPRIGHT = "_WALKING_UPRIGHT";
const string CREATURE_KEYWORD_WALKING_RIGHT = "_WALKING_RIGHT";
const string CREATURE_KEYWORD_WALKING_DOWNRIGHT = "_WALKING_DOWNRIGHT";
const string CREATURE_KEYWORD_WALKING_DOWN = "_WALKING_DOWN";
const string CREATURE_KEYWORD_WALKING_DOWNLEFT = "_WALKING_DOWNLEFT";
const string CREATURE_KEYWORD_WALKING_LEFT = "_WALKING_LEFT";
const string CREATURE_KEYWORD_WALKING_UPLEFT = "_WALKING_UPLEFT";
const string CREATURE_KEYWORD_STANDING_UP = "_STANDING_UP";
const string CREATURE_KEYWORD_STANDING_UPRIGHT = "_STANDING_UPRIGHT";
const string CREATURE_KEYWORD_STANDING_RIGHT = "_STANDING_RIGHT";
const string CREATURE_KEYWORD_STANDING_DOWNRIGHT = "_STANDING_DOWNRIGHT";
const string CREATURE_KEYWORD_STANDING_DOWN = "_STANDING_DOWN";
const string CREATURE_KEYWORD_STANDING_DOWNLEFT = "_STANDING_DOWNLEFT";
const string CREATURE_KEYWORD_STANDING_LEFT = "_STANDING_LEFT";
const string CREATURE_KEYWORD_STANDING_UPLEFT = "_STANDING_UPLEFT";
const string CREATURE_KEYWORD_HURT_UP = "_HURT_UP";
const string CREATURE_KEYWORD_HURT_UPRIGHT = "_HURT_UPRIGHT";
const string CREATURE_KEYWORD_HURT_RIGHT = "_HURT_RIGHT";
const string CREATURE_KEYWORD_HURT_DOWNRIGHT = "_HURT_DOWNRIGHT";
const string CREATURE_KEYWORD_HURT_DOWN = "_HURT_DOWN";
const string CREATURE_KEYWORD_HURT_DOWNLEFT = "_HURT_DOWNLEFT";
const string CREATURE_KEYWORD_HURT_LEFT = "_HURT_LEFT";
const string CREATURE_KEYWORD_HURT_UPLEFT = "_HURT_UPLEFT";
const string CREATURE_KEYWORD_FALLING_UP = "_FALLING_UP";
const string CREATURE_KEYWORD_FALLING_UPRIGHT = "_FALLING_UPRIGHT";
const string CREATURE_KEYWORD_FALLING_RIGHT = "_FALLING_RIGHT";
const string CREATURE_KEYWORD_FALLING_DOWNRIGHT = "_FALLING_DOWNRIGHT";
const string CREATURE_KEYWORD_FALLING_DOWN = "_FALLING_DOWN";
const string CREATURE_KEYWORD_FALLING_DOWNLEFT = "_FALLING_DOWNLEFT";
const string CREATURE_KEYWORD_FALLING_LEFT = "_FALLING_LEFT";
const string CREATURE_KEYWORD_FALLING_UPLEFT = "_FALLING_UPLEFT";

Creature::Creature(const string& name, const EntityTemplate& temp, const string& alig, unsigned int health) : Entity(name,
																													 health,
																													 temp.collisionArea),
	mFacingDirection(DIR_DOWN),
	mXVelocity(0),
	mYVelocity(0),
	mSpeed(1),
	mIsSearching(false),
	mIsWandering(false),
	mSearchSpan(0),
	mSearchDistance(0),
	mCreatureAnimationState(CREATUREANIMATION_STANDING)
{
	// This is a creature.
	mType = ENTITY_CREATURE;

	// Set the alignment.
	setAlignment(alig);

	// Load the animations.
	mLoadAnimations(temp.animation);

    // Looking down, by default.
    mSetAnimation(CREATUREANIMATION_STANDING);

    // Start the timers.
    mMovementTimer.start();
    mAttackTimer.start();
}

Creature::Creature(const string& data) : Entity("name", 0, Rectangle(0, 0, 0, 0)) // @todo need to implement loading creatures in this way.
{
}

Creature::~Creature()
{
    // Need to delete the actions here, because if I wait until the creature is deleted, certain
    // objects that are part of an entity (or other sub-classes) may get removed while still
    // needing the creature-like aspects of this object {cough cough moveToAction() cough cough}
    clearActions();
}

void Creature::mCollision(Entity& collidee)
{
	//@todo reimplement
//	// If the collidee is an enemy then focus on it and attack it.
//	if(collidee.getAlignment() != "NEUTRAL" && collidee.getAlignment() != getAlignment()) // @todo Create a constant 'NEUTRAL' alignment string?
//	{
//		// Stop first.
//		mSoftStop();
//
//		// First, grab onto the creature.
//		collidee.grab(this);
//
//		// This creature should set the victim as well.
//		mVictim = &collidee;
//
//		// Listen for when this creature has died, too.
//		collidee.addDeathListener(this);
//	}
}

void Creature::mDie()
{
	// Stop doing stuff.
	stop();
	mMovementTimer.stop();

	// Finish killing the creature.
	Entity::mDie();

    // Play the death sound.
    addAction(new PlaySoundAction("Game Sounds/PlayerDeath.ogg", 0)); // @todo I want to use a string constant here.

	// Show the death animation.
	addAction(new DisplayCreatureAnimationAction(*this, CREATUREANIMATION_FALLING, 1));
}

const string& Creature::mGetAnimationKeyword(CreatureAnimationState animation)
{
	switch(animation)
	{
		case CREATUREANIMATION_WALKING:
		{
			switch(mFacingDirection)
			{
				case DIR_UP: return mWalkingUp;
				case DIR_UPRIGHT: return mWalkingUpRight;
				case DIR_RIGHT: return mWalkingRight;
				case DIR_DOWNRIGHT: return mWalkingDownRight;
				case DIR_DOWN: return mWalkingDown;
				case DIR_DOWNLEFT: return mWalkingDownLeft;
				case DIR_LEFT: return mWalkingLeft;
				case DIR_UPLEFT: return mWalkingUpLeft;
				default: throw runtime_error("Creature::mSetAnimation() -> Invalid direction.");
			}
			break;
		}
		case CREATUREANIMATION_STANDING:
		{
			switch(mFacingDirection)
			{
				case DIR_UP: return mStandingUp;
				case DIR_UPRIGHT: return mStandingUpRight;
				case DIR_RIGHT: return mStandingRight;
				case DIR_DOWNRIGHT: return mStandingDownRight;
				case DIR_DOWN: return mStandingDown;
				case DIR_DOWNLEFT: return mStandingDownLeft;
				case DIR_LEFT: return mStandingLeft;
				case DIR_UPLEFT: return mStandingUpLeft;
				default: throw runtime_error("Creature::mSetAnimation() -> Invalid direction.");
			}
			break;
		}
		case CREATUREANIMATION_HURT:
		{
			switch(mFacingDirection)
			{
				case DIR_UP: return mHurtUp;
				case DIR_UPRIGHT: return mHurtUpRight;
				case DIR_RIGHT: return mHurtRight;
				case DIR_DOWNRIGHT: return mHurtDownRight;
				case DIR_DOWN: return mHurtDown;
				case DIR_DOWNLEFT: return mHurtDownLeft;
				case DIR_LEFT: return mHurtLeft;
				case DIR_UPLEFT: return mHurtUpLeft;
				default: throw runtime_error("Creature::mSetAnimation() -> Invalid direction.");
			}
			break;
		}
		case CREATUREANIMATION_FALLING:
		{
			switch(mFacingDirection)
			{
				case DIR_UP: return mFallingUp;
				case DIR_UPRIGHT: return mFallingUpRight;
				case DIR_RIGHT: return mFallingRight;
				case DIR_DOWNRIGHT: return mFallingDownRight;
				case DIR_DOWN: return mFallingDown;
				case DIR_DOWNLEFT: return mFallingDownLeft;
				case DIR_LEFT: return mFallingLeft;
				case DIR_UPLEFT: return mFallingUpLeft;
				default: throw runtime_error("Creature::mSetAnimation() -> Invalid direction.");
			}
			break;
		}
		default:
		{
			throw runtime_error("Creature::mSetAnimation() -> Invalid animation requested.  Make sure all creatures are provided with all required animations.");
		}
	}
}

Quadrilateral Creature::mGetAreaInFront(unsigned int span, int xOffset, int yOffset) const
{
	return getIsoscelesTrapezoid(getDimension().getCenter() + Vector(xOffset, yOffset), getFacingVector(), span, (getWidth() + getHeight()) / 2, (getWidth() + getHeight()) / 2);
}

void Creature::mLoadAnimations(const string& prefix)
{
	mWalkingUp = prefix + CREATURE_KEYWORD_WALKING_UP;
	mWalkingUpRight = prefix + CREATURE_KEYWORD_WALKING_UPRIGHT;
	mWalkingRight = prefix + CREATURE_KEYWORD_WALKING_RIGHT;
	mWalkingDownRight = prefix + CREATURE_KEYWORD_WALKING_DOWNRIGHT;
	mWalkingDown = prefix + CREATURE_KEYWORD_WALKING_DOWN;
	mWalkingDownLeft = prefix + CREATURE_KEYWORD_WALKING_DOWNLEFT;
	mWalkingLeft = prefix + CREATURE_KEYWORD_WALKING_LEFT;
	mWalkingUpLeft = prefix + CREATURE_KEYWORD_WALKING_UPLEFT;
	mStandingUp = prefix + CREATURE_KEYWORD_STANDING_UP;
	mStandingUpRight = prefix + CREATURE_KEYWORD_STANDING_UPRIGHT;
	mStandingRight = prefix + CREATURE_KEYWORD_STANDING_RIGHT;
	mStandingDownRight = prefix + CREATURE_KEYWORD_STANDING_DOWNRIGHT;
	mStandingDown = prefix + CREATURE_KEYWORD_STANDING_DOWN;
	mStandingDownLeft = prefix + CREATURE_KEYWORD_STANDING_DOWNLEFT;
	mStandingLeft = prefix + CREATURE_KEYWORD_STANDING_LEFT;
	mStandingUpLeft = prefix + CREATURE_KEYWORD_STANDING_UPLEFT;
	mHurtUp = prefix + CREATURE_KEYWORD_HURT_UP;
	mHurtUpRight = prefix + CREATURE_KEYWORD_HURT_UPRIGHT;
	mHurtRight = prefix + CREATURE_KEYWORD_HURT_RIGHT;
	mHurtDownRight = prefix + CREATURE_KEYWORD_HURT_DOWNRIGHT;
	mHurtDown = prefix + CREATURE_KEYWORD_HURT_DOWN;
	mHurtDownLeft = prefix + CREATURE_KEYWORD_HURT_DOWNLEFT;
	mHurtLeft = prefix + CREATURE_KEYWORD_HURT_LEFT;
	mHurtUpLeft = prefix + CREATURE_KEYWORD_HURT_LEFT;
	mFallingUp = prefix + CREATURE_KEYWORD_FALLING_UP;
	mFallingUpRight = prefix + CREATURE_KEYWORD_FALLING_UPRIGHT;
	mFallingRight = prefix + CREATURE_KEYWORD_FALLING_RIGHT;
	mFallingDownRight = prefix + CREATURE_KEYWORD_FALLING_DOWNRIGHT;
	mFallingDown = prefix + CREATURE_KEYWORD_FALLING_DOWN;
	mFallingDownLeft = prefix + CREATURE_KEYWORD_FALLING_DOWNLEFT;
	mFallingLeft = prefix + CREATURE_KEYWORD_FALLING_LEFT;
	mFallingUpLeft = prefix + CREATURE_KEYWORD_FALLING_UPLEFT;
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

void Creature::mSetAnimation(CreatureAnimationState animation)
{
	// Get the new animation.
	Sprite sprite = AnimationManager::get(mGetAnimationKeyword(animation));

	// Set the frame.
	sprite.setFrame(mSprite.getFrame());

	// Set the new animation.
	Entity::mSetAnimation(sprite);

	// Set the new state.
	mCreatureAnimationState = animation;
}

void Creature::mSoftStop()
{
    // Stop all movements.
    mXVelocity = mYVelocity = 0;

	// Set the stopped movement animation.
	mSetAnimation(CREATUREANIMATION_STANDING);

    // Consider the creature to have moved to it's point.
    mMovedToVector();
}

void Creature::addCreatureMovedToPointListener(CreatureMovedToPointListener* listener)
{
    mMovedToPointListeners.push_back(listener);
}

void Creature::deathOccurred(Entity& entity)
{
	//@todo needed?
}

Item* Creature::dropItem(const string& name)
{
	for(list<Item*>::iterator it = mHeldItems.begin(); it != mHeldItems.end(); ++it)
	{
		if((*it)->getName() == name)
		{
			Item* item = *it;
			mHeldItems.remove(item);
			return item;
		}
	}
	return 0;
}

Direction Creature::getFacingDirection() const
{
    return mFacingDirection;
}

const Vector& Creature::getFacingVector() const
{
	return mLookingAt;
}

double Creature::getSpeed() const
{
    return mSpeed;
}

bool Creature::isSearching() const
{
	return mIsSearching;
}

bool Creature::isWandering() const
{
    return mIsWandering;
}

void Creature::kill()
{
	// Kill the creature.
	mDie();
}

void Creature::logic(Level& level)
{
	// Only do most logic if the creature isn't dead.
	if(!isDead())
	{
//		// Search if the creature is searching and has not found a victim.
//		if(!mVictim && isSearching())
//		{
//			set<Entity*> e_set;
//			e_set.insert(this);
//			set<Entity*> spotted = eData.checkCollision(getIsoscelesTrapezoid(getVisibleArea().getCenter(), getFacingVector(), 175, (getWidth() + getHeight()) / 2, 275), e_set);
//			if(!spotted.empty())
//			{
//				// This is a set of victims.
//				set<Entity*> victims;
//
//				for(set<Entity*>::iterator it = spotted.begin(); it != spotted.end(); ++it)
//				{
//					// If this is an enemy (not NEUTRAL and not of the same alignment, then attack!
//					if((*it)->getAlignment() != "NEUTRAL" && (*it)->getAlignment() != getAlignment())
//					{
//						// Store the victims.
//						victims.insert(*it);
//					}
//				}
//
//				// If there weren't any victims, then continue on.  Otherwise run over to the closest victim.
//				if(!victims.empty())
//				{
//					// Stop moving and doing stuff.
//					mSoftStop();
//					clearActions();
//
//					// Stop searching, look at the victim, move to where the entity is, and continue searching.
//					// @todo Improve the 'following a victim' code.
//					const Vector& vic_loc = getClosestEntity(victims, *this)->getDimension().getCenter();
//					lookAt(vic_loc);
//					setSearching(false);
//					addAction(new MoveToAction(*this, vic_loc));
//					addAction(new SetSearchingAction(*this, true));
//				}
//			}
//		}
//@todo review
//		// If the creature is attacking, then do so before the movement (this way there will be a logic call between fighting and moving).
//		if(mVictim && mAttackTimer.getTime() >= CREATURE_ATTACK_INTERVAL)
//		{
//			// Do damage.
//			mVictim->damage(35);// @todo How much damage? how should it be incremented
//
//			// Restart the attack timer.
//			mAttackTimer.start();
//		}

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
//					set<Entity*> e_set = eData.checkCollision(*this);@todo review
//					if(!e_set.empty())
					if(level.checkMapCollision(*this))
					{
						// Return to the previous X position.
						setX(getX() - (mXVelocity * CREATURE_MOVEMENT_DISTANCE));

						// Hit the X side.
						xCollide = true;

//						// Check and handle collisions.
//						for(set<Entity*>::iterator it = e_set.begin(); it != e_set.end(); ++it)
//						{
//							mCollision(*(*it));
//						}
					}
				}
				if(mYVelocity)
				{
					// Update the Y position and check for a collision.
					setY(getY() + (mYVelocity * CREATURE_MOVEMENT_DISTANCE));
//					set<Entity*> e_set = eData.checkCollision(*this); @todo review
//					if(!e_set.empty())
					if(level.checkMapCollision(*this))
					{
						// Return to the previous Y position.
						setY(getY() - (mYVelocity * CREATURE_MOVEMENT_DISTANCE));

						// Hit the Y side.
						yCollide = true;

//						// Check and handle collisions.
//						for(set<Entity*>::iterator it = e_set.begin(); it != e_set.end(); ++it)
//						{
//							mCollision(*(*it));
//						}
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
				// If either an X collision or a Y collision did NOT occur and the creature is moving then tell the listeners of a movement event.
				else if(!xCollide && !yCollide && (mXVelocity || mYVelocity))
				{
					// Tell the movement listeners.
					mPushMovementEvent();
				}
			}

			// If the creature was moving at the beginning of this logic call but isn't now, then it has stopped.
			if(mXVelocity == 0 && mYVelocity == 0)
			{
				mSoftStop();
			}
		}

		// If the creature is looking at something different, then change the currently facing direction animation.
		// @note The creature should only be able to change directions if it's walking or standing.
		Direction new_dir = directionToPoint(getVisibleArea().getCenter(), mLookingAt);
		if(new_dir != mFacingDirection && (mCreatureAnimationState == CREATUREANIMATION_WALKING || mCreatureAnimationState == CREATUREANIMATION_STANDING))
		{
			// Set the newly facing direction for the current animation state.
			mFacingDirection = new_dir;
			mSetAnimation(mCreatureAnimationState);
		}

		// @fixme I shouldn't need this blank if statement...  Creature movement states seems to be tricky for me.
		//		  look into changing it when an NPC class is implemented.
		if(mCreatureAnimationState == CREATUREANIMATION_HURT || mCreatureAnimationState == CREATUREANIMATION_FALLING)
		{
			// hmm...
		}
		// If the creature moving differently now than it was in the last logic call, then either walk or stop walking.
		else if((mXVelocity != 0 || mYVelocity != 0) && mCreatureAnimationState != CREATUREANIMATION_WALKING)
		{
			mSetAnimation(CREATUREANIMATION_WALKING);
		}
		else if((mXVelocity == 0 && mYVelocity == 0) && mCreatureAnimationState != CREATUREANIMATION_STANDING)
		{
			mSetAnimation(CREATUREANIMATION_STANDING);
		}
	}

//	// Perform logic for any held items. @todo review how guns/other 'held' items would work
//	for(list<Item*>::iterator it = mHeldItems.begin(); it != mHeldItems.end(); ++it)
//	{
//		(*it)->heldLogic(eData, *this);
//	}

    // Call the entity's logic.
    Entity::logic(level);
}

void Creature::lookAt(const Vector& point)
{
	mLookingAt = point;
}

void Creature::moveTo(int x, int y)
{
    // Set the waypoint.
    mWaypoint.x = x;
    mWaypoint.y = y;

    // Look at the waypoint (actually, look a bit past the waypoint, so when
    // you get close to it you don't turn around)
    mLookingAt = getVectorOnLine(getDimension().getCenter(),
                                mWaypoint,
                                getDistance(getDimension().getCenter(),mWaypoint) + 20);

    // Update the velocities.
	mXVelocity = (getX() < x) ? 1 : ((getX() == x) ? 0 : -1);
	mYVelocity = (getY() < y) ? 1 : ((getY() == y) ? 0 : -1);
}

void Creature::pickupItem(Item& item)
{
	mHeldItems.push_back(&item);
}

void Creature::removeCreatureMovedToPointListener(CreatureMovedToPointListener* listener)
{
    mMovedToPointListeners.remove(listener);
}

void Creature::setSearchArea(unsigned int span, unsigned int distance)
{
	mSearchSpan = span;
	mSearchDistance = distance;
}

void Creature::setSearching(bool state)
{
	mIsSearching = state;
}

void Creature::setSpeed(double speed)
{
    mSpeed = (speed < 0.0) ? 0.0 : speed;
}

void Creature::setWandering(bool state)
{
    mIsWandering = state;
}

void Creature::stop()
{
	// Do a regular soft stop first.
	mSoftStop();

	// Stop wandering.
	setWandering(false);

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
    if(isWandering())
    {
        addAction(new WanderAction(this));
    }
}

const int Creature::WANDER_PAUSE_TIME = 4000;

const int Creature::CREATURE_PAUSE_TIME_BETWEEN_MOVEMENTS = 2500;
