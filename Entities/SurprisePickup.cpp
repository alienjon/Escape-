/*
 * SurprisePickup.cpp
 *
 *  Created on: Feb 2, 2013
 *      Author: alienjon
 */
#include "SurprisePickup.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../main.hpp"
#include "../Engine/VideoManager.hpp"

SurprisePickup::SurprisePickup(Level& level) :
	mLevel(level)
{
	mType = ENTITY_SURPRISEPICKUP;
	mSprite.addFrame(VideoManager::getTexture(IMAGE_SURPRISEPICKUP));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

SurprisePickup::~SurprisePickup()
{
}

void SurprisePickup::collide(Entity& entity)
{
	if(entity.getType() == ENTITY_PLAYER)
	{
		// Randomly select what is being done.
		int n = random(1, 100);
		if(n <= 25)
			mLevel.teleportPlayer();
		else if(n <= 50)
		{
			distributeChangeScore(5);
			distributeFloatingText("5", sf::Vector2f(entity.getX() + entity.getWidth(), entity.getY()));
		}
		else if(n <= 85)
		{
			distributeChangeScore(-25);
			distributeFloatingText("-25", sf::Vector2f(entity.getX() + entity.getWidth(), entity.getY()));
		}
		else
		{
			distributeChangeScore(175);
			distributeFloatingText("175", sf::Vector2f(entity.getX() + entity.getWidth(), entity.getY()));
		}

		// Get rid of the entity.
		mDie();

		// Play a pickup sound.
		AudioManager::playSound(SOUND_SURPRISEPICKUP);
	}
}
