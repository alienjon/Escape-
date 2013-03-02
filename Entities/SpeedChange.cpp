/*
 * SpeedChange.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: alienjon
 */
#include "SpeedChange.hpp"

#include <string>

#include "../Engine/AudioManager.hpp"
#include "../Entities/Creature.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Entities/Player.hpp"
#include "../Engine/VideoManager.hpp"

using std::string;

const unsigned int SPEEDCHANGE_INCREASE_INTERVAL = 3000;
const unsigned int SPEEDCHANGE_DECREASE_INTERVAL = 7000;

SpeedChange::SpeedChange(float speed, Creature& creature) :
	mSpeedTo(speed),
	mSpeedFrom(creature.getSpeed()),
	mCreature(creature)
{
	mType = ENTITY_SPEEDCHANGE;
	if(mSpeedTo < mSpeedFrom)
		mSprite.addFrame(VideoManager::getTexture(IMAGE_SLOWPLAYER));
	else
		mSprite.addFrame(VideoManager::getTexture(IMAGE_FASTPLAYER));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void SpeedChange::collide(Entity& entity)
{
	// If the entity is the creature being looked for, set it's speed.
	if(&entity == &mCreature)
	{
		// Change the player's speed.
		mCreature.setSpeed(mSpeedTo);

		// Configure the timer.
		mTimer.start();

		// Display what's happening.
		string txt = (mSpeedTo < mSpeedFrom) ? "Slow!" : "Fast!";
		distributeFloatingText(txt, sf::Vector2f(getX() - (getWidth() / 2), getY() - (getHeight() / 2)), sf::Color::Red);

		// Hide and stop displaying the entity.
		setInteractable(false);
		setCollidable(false);

		// Play the pickup sound.
		AudioManager::playSound(SOUND_PICKUP_SPECIAL);
	}
}

void SpeedChange::draw(sf::RenderWindow& renderer)
{
	if(!mTimer.isStarted())
		Entity::draw(renderer);
}

void SpeedChange::logic(Level& level, int delta)
{
	Entity::logic(level, delta);

	if(mTimer.isStarted() &&
	   ((mTimer.getTime() >= SPEEDCHANGE_INCREASE_INTERVAL && mSpeedTo < mSpeedFrom) ||
	   (mTimer.getTime() >= SPEEDCHANGE_DECREASE_INTERVAL && mSpeedTo >= mSpeedFrom)))
	{
		distributeFloatingText("Speed Returned!", sf::Vector2f(mCreature.getX() - (mCreature.getWidth() / 2), mCreature.getY() - (mCreature.getHeight() / 2)), sf::Color::Red);
		mCreature.setSpeed(mSpeedFrom);
		mDie();
	}
}
