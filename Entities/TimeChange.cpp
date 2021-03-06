/*
 * TimeChange.cpp
 *
 *  Created on: Nov 29, 2011
 *      Author: alienjon
 */
#include "TimeChange.hpp"

#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../main.hpp"
#include "../Engine/VideoManager.hpp"

const unsigned int TIMECHANGE_INTERVAL_GAIN_MAX = 900;
const unsigned int TIMECHANGE_INTERVAL_GAIN_MIN = 300;
const unsigned int TIMECHANGE_INTERVAL_LOSS_MAX = 1500;
const unsigned int TIMECHANGE_INTERVAL_LOSS_MIN = 750;

const int TIMECHANGE_GAIN = -15000;
const int TIMECHANGE_LOSS = 30000;

using std::string;

TimeChange::TimeChange() :
	mIsAdding(false),
	mInterval(0)
{
	mType = ENTITY_TIMECHANGE;
	mSprite.addFrame(VideoManager::getTexture(IMAGE_TIMELOSS));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
	mTimer.start();
}

void TimeChange::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Add or subtract from the time.
		if(mIsAdding)
			distributeTimeChange(TIMECHANGE_GAIN);
		else
			distributeTimeChange(TIMECHANGE_LOSS);

		distributeFloatingText((mIsAdding ? "+" : "-") + string("00:") + toString((mIsAdding ? (TIMECHANGE_GAIN * -1) : TIMECHANGE_LOSS) / 1000), getPosition(), sf::Color::White);

		// Kill the pickup.
		mDie();

		// Play the pickup sound.
		AudioManager::playSound(SOUND_PICKUP_SPECIAL);
	}
}

void TimeChange::logic(Level& level, int delta)
{
	// Perform entity logic.
	Entity::logic(level, delta);

	// If time is up, set the interval, update the image, and switch time gain/loss state.
	if(mTimer.getTime() >= mInterval)
	{
		// I need to clear the animation sprite's frames first.
		mSprite.clear();
		if(mIsAdding)
		{
			mInterval = random(TIMECHANGE_INTERVAL_LOSS_MIN, TIMECHANGE_INTERVAL_LOSS_MAX);
			mSprite.addFrame(VideoManager::getTexture(IMAGE_TIMELOSS));
			mIsAdding = false;
		}
		else
		{
			mInterval = random(TIMECHANGE_INTERVAL_GAIN_MIN, TIMECHANGE_INTERVAL_GAIN_MAX);
			mSprite.addFrame(VideoManager::getTexture(IMAGE_TIMEGAIN));
			mIsAdding = true;
		}
		mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
		mTimer.start();
	}
}
