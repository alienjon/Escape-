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

void Entity::draw(sf::RenderWindow& renderer)
{
	renderer.draw(mSprite);
}

void Entity::logic(Level& level)
{
    // Update the action logic.
    ActionInterface::logic(level);
}

bool sortByZIndex(Entity* a, Entity* b)
{//@todo change to origin?
//	return a->getDimension().getOrigin().y < b->getDimension().getOrigin().y;
	return a->getY() < b->getY();
}
