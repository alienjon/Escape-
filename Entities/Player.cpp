/*
 * Player.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Player.hpp"

#include <set>
#include <stdexcept>

#include "../Engine/Colors.hpp"
#include "../Game/Level.hpp"
#include "../Engine/Logger.hpp"
#include "../Actions/MultipleActionsAction.hpp"
#include "../Actions/PlaySoundAction.hpp"

using std::list;
using std::runtime_error;
using std::set;

Player::Player() :
	mAllowInput(true),
	mIsInteracting(false)
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves at a normal speed.
    setSpeed(1.0);

    // Start the interacting timer.
    mInteractingTimer.start();

    //@todo remove when done.
    mSetSize(30, 30);
}

Player::~Player()
{
}

void Player::mDie()
{
    // Stop accepting player input.
    mAllowInput = false;

    // Continue dying.
    Creature::mDie();
}

void Player::collide(Entity& entity)
{
}

void Player::draw(Renderer& renderer)//@todo review and implement player drawing.
{
	renderer.setColor(COLOR_WHITE);
	renderer.fillRectangle(Rectangle(getDimension()));

	// For each color lock, draw it on the player.@todo review - is this how I want to do this?
	Rectangle area = getDimension();
	unsigned int size = area.width / (mLocks.size() + 1);
	for(list<gcn::Color>::const_iterator it = mLocks.begin(); it != mLocks.end(); ++it)
	{
		area.width = (area.width > size) ? area.width - size : size;
		area.height= (area.height> size) ? area.height- size : size;
		area.vector.x = getX() + (getWidth() / 2) - (area.width / 2);
		area.vector.y = getY() + (getHeight()/ 2) - (area.height/ 2);
		renderer.setColor(*it);
		renderer.fillRectangle(area);
	}
}

void Player::handleInput(const Input& input)
{
	// Reset the velocity.
	mXVelocity = mYVelocity = 0;

	// Unset the interaction.
	mIsInteracting = false;

	// Check for allowing input.
    if(!mAllowInput)
    {
        return;
    }

    // Calculate the velocity.
    if(input.isKeyPressed(SDLK_w))
    {
    	mYVelocity--;
    }

    if(input.isKeyPressed(SDLK_s))
    {
    	mYVelocity++;
    }

    if(input.isKeyPressed(SDLK_a))
    {
    	mXVelocity--;
    }

    if(input.isKeyPressed(SDLK_d))
    {
    	mXVelocity++;
    }

    // Press 'SPACE' or the left mouse button to interact.
    if((input.isKeyClicked(SDLK_SPACE) || input.isMousePressed(SDL_BUTTON_LEFT)) && mInteractingTimer.getTime() >= 250)
    {
    	mIsInteracting = true;
    	mInteractingTimer.start();
    }
}

const SDLKey PLAYER_ACTION_KEY = SDLK_SPACE;
const int Player::PLAYER_ACTION_DISTANCE = 2;
