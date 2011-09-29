/*
 * Item
 *
 *  Created on: Aug 18, 2009
 *      Author: alienjon
 */

#include "Item.hpp"

#include "../../Managers/AnimationManager.hpp"
#include "../../Math/Rectangle.hpp"

Item::Item(const std::string& name, const EntityTemplate& temp) : Entity(name, 0, temp.collisionArea)
{
	// This is an item.
	mType = ENTITY_ITEM;

	// Set the alignment.
	setAlignment("NEUTRAL");

	// Set the animation.
	mSetAnimation(AnimationManager::get(temp.animation));
}

void Item::mPushedBack(Direction dir)
{
}

void Item::damage(unsigned int damage)
{
}

//void Item::heldLogic(EnvironmentData& eData, Creature& holder)@todo review
//{
//	// Nada, for the default item.
//}

void Item::push(Direction dir, unsigned int force)
{
}
