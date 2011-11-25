/*
 * Key.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#include "KeyEntity.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"

const float KEYENTITY_MAXSIZE = 35.f;
const float KEYENTITY_MINSIZE = 5.f;

KeyEntity::KeyEntity(sf::Color color) :
	mColor(color),
	mIsGrowing(true)
{
	mType = ENTITY_KEY;
	mTimer.start();
}

void KeyEntity::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Distribute information that the lock was picked up.
		distributeAddLock(mColor);
		distributeRemoveLock(mColor);
		distributeFloatingText("Key", sf::Vector2f(getX() + getWidth(), getY()), mColor);

		// Add to the score.
		distributeChangeScore(50);//@todo how many points should be awarded for obtaining a key?

		// Kill the entity.
		mDie();

		// Play a sound.
		AudioManager::playSound(SOUND_PICKUP_KEY);
	}
}

void KeyEntity::logic(Level& level)
{
	// Perform entity logic.
	Entity::logic(level);

	// Grow or shrink the key.
	if(mTimer.getTime() >= 10)
	{
		if(mIsGrowing)
		{
			mSize.x += 0.2;
			mSize.y += 0.2;
			if(mSize.x >= KEYENTITY_MAXSIZE)
			{
				mSize.x = mSize.y = KEYENTITY_MAXSIZE;
				mIsGrowing = false;
			}
		}
		else
		{
			mSize.x -= 0.2;
			mSize.y -= 0.2;
			if(mSize.x <= KEYENTITY_MINSIZE)
			{
				mSize.x = mSize.y = KEYENTITY_MINSIZE;
				mIsGrowing = true;
			}
		}
		sf::Vector2f pos = getPosition();
		mSprite = sf::Shape::Rectangle(-(mSize.x / 2), -(mSize.y / 2), mSize.x, mSize.y, mColor);
		setPosition(pos.x, pos.y);
		mTimer.start();
	}
}
