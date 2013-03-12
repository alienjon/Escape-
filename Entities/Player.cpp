/*
 * Player.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Player.hpp"

#include "../Game/Keywords.hpp"
#include "../Engine/VideoManager.hpp"

using std::list;

Player::Player() :
	mHasInput(true)
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves at a normal speed.
    setSpeed(1.f);

    // Setup the player's size.
	mSprite.addFrame(VideoManager::getTexture(IMAGE_PLAYER));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void Player::collide(Entity& entity)
{
	// The player doesn't do any collision work.  If a collision does occur, then
	// it is because another moving creature collided with the player.  Do that
	// creature's collision.
	entity.collide(*this);
}

bool Player::handleInput(const sf::Event& event)
{
	// Only perform input if allowed.
	if(!mHasInput)
		return false;

	if(event.type == sf::Event::KeyPressed)
	{
		// Calculate the velocity.
		if(event.key.code == sf::Keyboard::Up)
			mUp = true;
		if(event.key.code == sf::Keyboard::Down)
			mDown = true;
		if(event.key.code == sf::Keyboard::Left)
			mLeft = true;
		if(event.key.code == sf::Keyboard::Right)
			mRight = true;
		return true;
	}
	else if(event.type == sf::Event::KeyReleased)
	{
		if(event.key.code == sf::Keyboard::Up)
			mUp = false;
		if(event.key.code == sf::Keyboard::Down)
			mDown = false;
		if(event.key.code == sf::Keyboard::Left)
			mLeft = false;
		if(event.key.code == sf::Keyboard::Right)
			mRight = false;
		return true;
	}

	// Nothing happened.
	return false;
}

const sf::Keyboard::Key PLAYER_ACTION_KEY = sf::Keyboard::Space;
const int Player::PLAYER_ACTION_DISTANCE = 2;
