/*
 * ZoomScreen.cpp
 *
 *  Created on: Nov 25, 2011
 *      Author: alienjon
 */
#include "ZoomScreen.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Engine/VideoManager.hpp"

const unsigned int ZOOM_INTERVAL = 5;
const float ZOOM_STEP = 1.015f;

ZoomScreen::ZoomScreen(Level& level) :
	mLevel(level),
	mIsZooming(true)
{
	mType = ENTITY_ZOOM;
	mSprite = sf::Sprite(VideoManager::getTexture(IMAGE_ZOOMSCREEN));
	adjustSize();
	mSprite.SetOrigin(getWidth() / 2, getHeight() / 2);
	mTimer.start();
}

void ZoomScreen::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Flip the screen.
		mLevel.zoom();

		// Display what's happening.
		distributeFloatingText("Zoomed!", sf::Vector2f(getX() - (getWidth() / 2), getY() - (getHeight() / 2)), sf::Color::Red);

		// Kill the pickup.
		mDie();

		// Play the pickup sound.
		AudioManager::playSound(SOUND_PICKUP_SPECIAL);
	}
}

void ZoomScreen::logic(Level& level)
{
	if(mTimer.getTime() >= ZOOM_INTERVAL)
	{
		if(mIsZooming)
		{
			mSprite.Scale(ZOOM_STEP, ZOOM_STEP);
			if(mSprite.GetScale().x >= 2.5f)
				mIsZooming = false;
		}
		else
		{
			mSprite.Scale(1/ZOOM_STEP, 1/ZOOM_STEP);
			if(mSprite.GetScale().x <= 0.3f)
				mIsZooming = true;
		}
		adjustSize();
		level.checkEntityCollision(*this);
		mTimer.start();
	}
}
