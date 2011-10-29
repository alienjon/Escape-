/*
 * Entity.cpp
 *
 *  Created on: Jun 25, 2009
 *      Author: alienjon
 */
#include "Entity.hpp"

#include "../Game/Level.hpp"

using std::list;
using std::string;

Entity::Entity() :
	mType(ENTITY_NULL),
	mIsCollidable(true),
	mIsInteractable(true)
{
}

Entity::~Entity()
{
    // Clear any remaining actions.
    clearActions();
}

void Entity::mDie()
{
	// The entity isn't collidable anymore.
	setCollidable(false);

    // Tell any listeners.
    for(list<DeathListener*>::iterator it = mDeathListeners.begin(); it != mDeathListeners.end(); ++it)
    {
        (*it)->deathOccurred(this);
    }
}

void Entity::mSetAnimation(const Sprite& sprite)//@fixme cleanup how the collision area is calculated.
{
	// Set the sprite.
    mSprite = sprite;

    // Make sure it is animating.
    mSprite.setAnimating(true);

    // Update the dimension.
    mDimension = Rectangle(mDimension.vector.x, mDimension.vector.y, mSprite.getWidth(), mSprite.getHeight());
}

void Entity::draw(Renderer& renderer)
{
    // Just need to draw ourselves.
    mSprite.draw(renderer, getPosition());
}

void Entity::logic(Level& level)
{
    // Update the being's display.
    mSprite.logic();

    // Update the action logic.
//    ActionInterface::logic(eData); @todo review.
}

void Entity::setPosition(double x, double y)
{
	setX(x);
	setY(y);
}

bool sortByZIndex(const Entity* beingA, const Entity* beingB)
{
	return beingA->getDimension().getCenter().y < beingB->getDimension().getCenter().y;
}
