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
	// This is the magic pink to make unchanged colors obvious.
	mSprite.SetColor(sf::Color::Magenta);
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
	renderer.Draw(mSprite);
}

void Entity::logic(Level& level)
{
    // Update the action logic.
    ActionInterface::logic(level);
}

bool sortByZIndex(const Entity* a, const Entity* b)
{
	return a->getDimension().GetOrigin().y < b->getDimension().GetOrigin().y;
}
