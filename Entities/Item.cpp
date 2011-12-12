/*
 * Item.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#include "Item.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Entities/Creature.hpp"
#include "../Game/Keywords.hpp"

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

			// Play the pickup sound.
			AudioManager::playSound(SOUND_PICKUP_SPECIAL);
		}
}

void Item::draw(sf::RenderWindow& renderer)
{
	if(mIsDrawing)
		ImageEntity::draw(renderer);
}

void Item::use(Creature& creature)
{
	// Play the pickup sound.
	AudioManager::playSound(SOUND_PICKUP_SPECIAL);

	mPerform(creature);
	mDie();
}
