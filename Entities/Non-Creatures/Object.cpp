/*
 * Object.cpp
 *
 *  Created on: Jun 16, 2010
 *      Author: the-saint
 */

#include "Object.hpp"

#include "../../Managers/AnimationManager.hpp"
#include "../../Entities/EntityType.hpp"

using std::string;

Object::Object(const string& name, const EntityTemplate& temp) : Entity(name, 100, 100, temp.collisionArea) // @todo need to implement adding health/defense to objects
{
	// Set the type.
	mType = ENTITY_OBJECT;

	// Set the alignment.
	setAlignment("NEUTRAL");

	// Set the animation.
	mSetAnimation(AnimationManager::get(temp.animation));
}

Object::Object(const string& data) : Entity("LOADED OBJECT", 0, 0, Rectangle(0, 0, 0, 0)) // @todo name of a loaded object?
{
// @todo configure a loaded object
}

void Object::mPushed(Direction dir)
{
	// @todo Some objects can be pushed, others cannot
}

void Object::damage(unsigned int value)
{
	// Objects cannot be damaged.
}

std::string Object::extract() const
{
// @todo implement extraction for saving.
	return "";
}

void Object::push(Direction dir, unsigned int force)
{
// @todo need to implement being pushed
}
