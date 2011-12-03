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
#include "../Engine/VideoManager.hpp"

using std::string;

const unsigned int SPEEDCHANGE_INCREASE_INTERVAL = 10000;
const unsigned int SPEEDCHANGE_DECREASE_INTERVAL = 15000;

SpeedChange::SpeedChange(float speed, Creature& creature) :
	mSpeed(speed),
	mCreature(creature)
{
	mType = ENTITY_SPEEDCHANGE;
	if(mSpeed < 1.f)
		mSprite = sf::Sprite(VideoManager::getTexture(IMAGE_SLOWPLAYER));
	else
		mSprite = sf::Sprite(VideoManager::getTexture(IMAGE_FASTPLAYER));
	adjustSize();
	mSprite.SetOrigin(getWidth() / 2, getHeight() / 2);
}

void SpeedChange::collide(Entity& entity)
{
	// If the entity is the creature being looked for, set it's speed.
	if(&entity == &mCreature)
	{
		// Change the player's speed.
		mCreature.setSpeed(mSpeed);

		// Configure the timer.
		mTimer.start();

		// Display what's happening.
		string txt = (mSpeed < 1.f) ? "Slow!" : "Fast!";
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
		ImageEntity::draw(renderer);
}

void SpeedChange::logic(Level& level)
{
	ImageEntity::logic(level);

	if(mTimer.isStarted() &&
	   ((mTimer.getTime() >= SPEEDCHANGE_INCREASE_INTERVAL && mSpeed < 1.f) ||
	   (mTimer.getTime() >= SPEEDCHANGE_DECREASE_INTERVAL && mSpeed >= 1.f)))
	{
		distributeFloatingText("Speed Returned!", sf::Vector2f(getX() - (getWidth() / 2), getY() - (getHeight() / 2)), sf::Color::Red);
		mCreature.setSpeed(1.f);
		mDie();
	}
}
