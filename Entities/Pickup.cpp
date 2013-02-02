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
#include "../Engine/VideoManager.hpp"

Pickup::Pickup(int value, const sf::Color& color, PickupSize size) :
	mValue(value)
{
	mType = ENTITY_PICKUP;
	mSprite.addFrame(VideoManager::getTexture(IMAGE_PICKUP));
	mSprite.setColor(color);
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
	switch(size)
	{
		case SMALL:
		{
			mSprite.scale(0.5, 0.5);
			break;
		}
		case LARGE:
		{
			mSprite.scale(2.5, 2.5);
			break;
		}
		default:
		{
			break;
		}
	}
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
