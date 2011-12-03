/*
 * FlipScreen.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: alienjon
 */
#include "FlipScreen.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Engine/VideoManager.hpp"

const unsigned int ROTATE_INTERVAL = 5;
const float ROTATE_STEP = -1.5f;

FlipScreen::FlipScreen(Level& level) :
	mLevel(level)
{
	mType = ENTITY_FLIP;
	mSprite = sf::Sprite(VideoManager::getTexture(IMAGE_FLIPSCREEN));
	adjustSize();
	mSprite.SetOrigin(getWidth() / 2, getHeight() / 2);
	mTimer.start();
}

void FlipScreen::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Flip the screen.
		mLevel.flip();

		// Display what's happening.
		distributeFloatingText("Flipped!", sf::Vector2f(getX() - (getWidth() / 2), getY() - (getHeight() / 2)), sf::Color::Red);

		// Kill the pickup.
		mDie();

		// Play the pickup sound.
		AudioManager::playSound(SOUND_PICKUP_SPECIAL);
	}
}

void FlipScreen::logic(Level& level)
{
	if(mTimer.getTime() >= ROTATE_INTERVAL)
	{
		mSprite.Rotate(ROTATE_STEP);
		mTimer.start();
	}
}
