/*
 * Entity.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: alienjon
 */
#include "Entity.hpp"

#include "../Entities/Alignment.hpp"
#include "../Engine/Colors.hpp"
#include "../Entities/Creatures/Creature.hpp"
#include "../Game/Game.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

using std::list;
using std::string;

const unsigned int ENTITY_DEFENSEREGENERATION_INTERVAL = 80;

Entity::Entity(const string& name, unsigned int maxHealth, unsigned int maxDefense, const Rectangle& collisionArea) :
	mId(mIdCounter++),
	mDefense(maxDefense),
	mMaxDefense(maxDefense),
	mDefenseRegenerationRate(1),
	mHealth(maxHealth),
	mMaxHealth(maxHealth),
	mCollidable(true),
	mAlignment(ALIGNMENT_NEUTRAL),
	mType(ENTITY_NULL),
	mName(name),
	mCollisionArea(collisionArea),
	mIsDead(false)
{
	// Start the defense regeneration timer.
	mDefenseRegenerationTimer.start();
}

Entity::~Entity()
{
    // Clear any remaining actions.
    clearActions();
}

void Entity::mCollision(Entity& collider)
{//@todo need a new way of letting the game know (if it needs to) that 2 entities collided
//	pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_COLLISION_ENTITY + CHAR_DELIMITER + getName() + CHAR_DELIMITER + collider.getName());
}

void Entity::mDie()
{
	// The entity isn't collidable anymore.
	mCollidable = false;

	// The entity is dead.
	mIsDead = true;
	mHealth = mDefense = 0;

    // Tell any listeners.
    for(list<DeathListener*>::iterator it = mDeathListeners.begin(); it != mDeathListeners.end(); ++it)
    {
        (*it)->deathOccurred(*this);
    }

    // Also call it as a plot event.//@todo need a new way to tell the game an entity died.
//    pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_DEATH + CHAR_DELIMITER_ALTERNATE + getName());
}

const Rectangle& Entity::mGetCollisionArea() const
{
	return mCollisionArea;
}

void Entity::mPushInteraction(Entity* actor)
{
    for(list<InteractionListener*>::iterator it = mInteractionListeners.begin(); it != mInteractionListeners.end(); ++it)
    {
        (*it)->interactionOccurred(actor, this);
    }
}

void Entity::mPushMovementEvent()
{
	for(list<MovementListener*>::const_iterator it = mMovementListeners.begin(); it != mMovementListeners.end(); ++it)
	{
		(*it)->entityMoved(*this);
	}
}

void Entity::mSetAnimation(const Sprite& sprite)
{
    mSprite = sprite;

    // Make sure it is animating.
    mSprite.setAnimating(true);

    // Update the collision offset.
    // NOTE: The cast to integer is used so that if the collision area happens to be larger than the image, the number
    // can safetly become negative during the calculation (since it is measured in 2 'widths', they are unsigned.
	mCollisionArea.vector.x = (mSprite.getWidth() / 2) - (int)(mCollisionArea.width / 2);
	mCollisionArea.vector.y = mSprite.getHeight() - mCollisionArea.height;
}

void Entity::addAnimationCycleListener(AnimationCycleListener* listener)
{
    mSprite.addAnimationCycleListener(listener);
}

void Entity::addDeathListener(DeathListener* listener)
{
    mDeathListeners.push_back(listener);
}

void Entity::addHealthChangedListener(HealthChangedListener* listener)
{
    mHealthChangedListener.push_back(listener);
}

void Entity::addInteractionListener(InteractionListener* listener)
{
    mInteractionListeners.push_back(listener);
}

void Entity::addMovementListener(MovementListener* listener)
{
	mMovementListeners.push_back(listener);
}

void Entity::damage(unsigned int value)
{
	// You can only damage a creature that is not already dead.
	if(mHealth == 0)
	{
		return;
	}

	// Damage the strength first.
	mDefense -= value;

	// If the defense went below zero, then set it to zero and subtract from health.
	if(mDefense < 0)
	{
		mHealth -= 0 - mDefense;
		mDefense = 0;
	}

    // If the health falls below zero, null it to zero and inform that the creature died.
    if(mHealth <= 0)
    {
        mHealth = 0;
        mDie();
    }

    // Tell the listeners the health has changed.
    for(list<HealthChangedListener*>::iterator it = mHealthChangedListener.begin(); it != mHealthChangedListener.end(); ++it)
    {
        (*it)->healthChanged(this);
    }

    // Also push a plot event.//@todo need a new way for the game to know that damage was taken by an entity.
//    pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_DAMAGE + CHAR_DELIMITER_ALTERNATE + getName());
}

void Entity::draw(Renderer& renderer)
{
    // Just need to draw ourselves.
	Vector pos = mPosition - Vector(mCollisionArea.vector.x, mCollisionArea.vector.y);
    mSprite.draw(renderer, pos);
}

string Entity::extract() const
{
	return "";
}

const string& Entity::getAlignment() const
{
    return mAlignment;
}

const int Entity::getDefense() const
{
    return mDefense;
}

const Rectangle Entity::getDimension() const
{
    return Rectangle(mPosition.x, mPosition.y, mCollisionArea.width, mCollisionArea.height);
}

unsigned int Entity::getHealth() const
{
	return (mHealth < 0) ? 0 : mHealth; // This should never be below 0 (it is managed in damage) but this makes sure of it.
}

unsigned int Entity::getHeight() const
{
    return mCollisionArea.height;
}

unsigned int Entity::getId() const
{
    return mId;
}

const int Entity::getMaxDefense() const
{
    return mMaxDefense;
}

unsigned int Entity::getMaxHealth() const
{
    return mMaxHealth;
}

const string& Entity::getName() const
{
	return mName;
}

const Vector& Entity::getPosition() const
{
    return mPosition;
}

EntityType Entity::getType() const
{
    return mType;
}

const Rectangle Entity::getVisibleArea() const
{
	return Rectangle(getX() - mCollisionArea.vector.x, getY() - mCollisionArea.vector.y, mSprite.getWidth(), mSprite.getHeight());
}

unsigned int Entity::getWidth() const
{
    return mCollisionArea.width;
}

const double& Entity::getX() const
{
    return mPosition.x;
}

const double& Entity::getY() const
{
    return mPosition.y;
}

void Entity::grab(Creature* creature)
{
	mHoldingAttackers.insert(creature);
}

void Entity::handleInput(const Input& input)
{
	// Most entities don't do input.
}

void Entity::interact(Entity& entity)
{
	// Basic entities don't do anything.
}

bool Entity::isCollidable() const
{
    return mCollidable;
}

bool Entity::isDead() const
{
	return mIsDead;
}

bool Entity::isIntersecting(const Quadrilateral& area) const
{
	// Does this entity's area intersect with the area and is it collidable?
	return mCollidable && area.isIntersecting(getDimension());
}

//void Entity::logic(EnvironmentData& eData)//@todo review
//{
//    // Update the being's display.
//    mSprite.logic();
//
//    // Update the action logic.
//    ActionInterface::logic(eData);
//
//    // If the defense timer has hit its interval, increase the defense value.
//    if(!isDead() && mDefense != (int)mMaxDefense && mDefenseRegenerationTimer.getTime() >= ENTITY_DEFENSEREGENERATION_INTERVAL)
//    {
//    	// Increase the value and restart the timer.
//    	unsigned int newValue = (mDefense + mDefenseRegenerationRate > 0) ? mDefense + mDefenseRegenerationRate : 0; // Just in case the defense regen rate is a negative number.
//    	mDefense = (newValue < mMaxDefense) ? newValue : mMaxDefense;
//    	mDefenseRegenerationTimer.start();
//
//        // Tell the listeners the health has changed.
//        for(list<HealthChangedListener*>::iterator it = mHealthChangedListener.begin(); it != mHealthChangedListener.end(); ++it)
//        {
//            (*it)->healthChanged(this);
//        }
//    }
//}

void Entity::lookAt(const Vector& point)
{
	// Entities aren't capable of looking.  This is for creatures.
}

void Entity::release(Creature* creature)
{
	mHoldingAttackers.erase(creature);
}

void Entity::removeAnimationCycleListener(AnimationCycleListener* listener)
{
    mSprite.removeAnimationCycleListener(listener);
}

void Entity::removeDeathListener(DeathListener* listener)
{
    mDeathListeners.remove(listener);
}

void Entity::removeHealthChangedListener(HealthChangedListener* listener)
{
    mHealthChangedListener.remove(listener);
}

void Entity::removeInteractionListener(InteractionListener* listener)
{
    mInteractionListeners.remove(listener);
}

void Entity::removeMovementListener(MovementListener* listener)
{
	mMovementListeners.remove(listener);
}

void Entity::setAlignment(const std::string& alignment)
{
    mAlignment = alignment;
}

void Entity::setAnimating(bool state)
{
    mSprite.setAnimating(state);
}

void Entity::setCollision(bool state)
{
	mCollidable = state;
}

void Entity::setPosition(double x, double y)
{
	setX(x);
	setY(y);
}

void Entity::setX(double x)
{
	mPosition.x = x;
}

void Entity::setY(double y)
{
	mPosition.y = y;
}

Entity* getClosestEntity(const std::set<Entity*>& collection, Entity& entity)
{
	Entity* ret = 0;
	for(std::set<Entity*>::iterator it = collection.begin(); it != collection.end(); ++it)
	{
		if(!ret || getDistance((*it)->getPosition(), entity.getPosition()) < getDistance(ret->getPosition(), entity.getPosition()))
		{
			ret = *it;
		}
	}
	return ret;
}

const uint SPRITE_INDICATOR_ANIMATION_INTERVAL = 150;
const int PUSH_DISTANCE = 80;

bool sortByZIndex(const Entity* beingA, const Entity* beingB)
{
	if(beingA->isDead())
	{
		return true;
	}
	else if(beingB->isDead())
	{
		return false;
	}
	else
	{
		return beingA->getDimension().getCenter().y < beingB->getDimension().getCenter().y;
	}
}

unsigned int Entity::mIdCounter = 0;
