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

FlipScreen::FlipScreen(Level& level) :
	mLevel(level)
{
	mSprite = sf::Shape::Circle(0, 0, 10, sf::Color::Red);
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
		AudioManager::playSound(SOUND_PICKUP);
	}
}
