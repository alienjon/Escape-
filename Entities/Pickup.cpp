/*
 * Pickup.cpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#include "Pickup.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

Pickup::Pickup(int value, const sf::Color& color, unsigned int size) :
	mValue(value),
	mSize(size)
{
	mType = ENTITY_PICKUP;
//	mSprite.setColor(color);@fixme Need sprite/animation for pickups
}

void Pickup::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Distribute information that the pickup was grabbed.
		distributeChangeScore(mValue);
		distributeFloatingText(toString(mValue), sf::Vector2f(getX() + getWidth(), getY()));

		// Kill the pickup.
		mDie();

		// Play the pickup sound.
		AudioManager::playSound(SOUND_PICKUP);
	}
}
