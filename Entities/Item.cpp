/*
 * Item.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#include "Item.hpp"

Item::Item() :
	mIsDrawing(true)
{
	mType = ENTITY_ITEM;
	setCollidable(false);
}

void Item::collide(Entity& entity)
{
	// Tell the player to pickup this item.
	if(entity.getType() == ENTITY_PLAYER)
		if(entity.pickup(*this))
		{
			setInteractable(false);
			mIsDrawing = false;
		}
}

void Item::draw(sf::RenderWindow& renderer)
{
	if(mIsDrawing)
		Entity::draw(renderer);
}

void Item::use()
{
	mPerform();
	mDie();
}
