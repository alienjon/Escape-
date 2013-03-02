/*
 * Player.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Player.hpp"

#include "../Game/Keywords.hpp"
#include "../Engine/VideoManager.hpp"

const unsigned int COLOR_CYCLE_TIME_INTERVAL = 1300;
const float PLAYER_SIZE = 50.f;
const float INTERNAL_SIZE = 10.f;
const sf::Color PLAYER_COLOR = sf::Color::Blue;

using std::list;

Player::Player() :
	mHasInput(true),
	mCycle(COLORCYCLE_MOVE),
	mColor1(mLocks.end()), mColor2(mLocks.end()), mColor3(mLocks.end()), mColor4(mLocks.end())
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves at a normal speed.
    setSpeed(1.f);

    // Start the timer.
    mColorCycleTimer.start();

    // Setup the player's size.
	mSprite.addFrame(VideoManager::getTexture(IMAGE_PLAYER));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);

    // Configure the internal sizes.
    mResetCyclePositions();
}

void Player::mResetCyclePositions()
{
    mCol1 = sf::FloatRect(PLAYER_SIZE * 0.02f, PLAYER_SIZE * 0.02f, PLAYER_SIZE * 0.46f, PLAYER_SIZE * 0.46f);
    mCol2 = sf::FloatRect(PLAYER_SIZE * 0.52f, PLAYER_SIZE * 0.02f, PLAYER_SIZE * 0.46f, PLAYER_SIZE * 0.46f);
    mCol3 = sf::FloatRect(PLAYER_SIZE * 0.52f, PLAYER_SIZE * 0.52f, PLAYER_SIZE * 0.46f, PLAYER_SIZE * 0.46f);
    mCol4 = sf::FloatRect(PLAYER_SIZE * 0.02f, PLAYER_SIZE * 0.52f, PLAYER_SIZE * 0.46f, PLAYER_SIZE * 0.46f);
}

void Player::collide(Entity& entity)
{
	// The player doesn't do any collision work.  If a collision does occur, then
	// it is because another moving creature collided with the player.  Do that
	// creature's collision.
	entity.collide(*this);
}

void Player::draw(sf::RenderWindow& renderer)
{
	// Draw the base creature.
	Creature::draw(renderer);

	// The drawing objects.
	sf::RectangleShape shape;

	// Draw the colors.
	if(mColor1 != mLocks.end())
	{
		shape.setSize(sf::Vector2f(mCol1.width, mCol1.width));
		shape.setPosition(getX() + mCol1.left, getY() + mCol1.top);
		shape.setFillColor(*mColor1);
		renderer.draw(shape);
	}
	if(mColor2 != mLocks.end())
	{
		shape.setSize(sf::Vector2f(mCol2.width, mCol2.width));
		shape.setPosition(getX() + mCol2.left, getY() + mCol2.top);
		shape.setFillColor(*mColor2);
		renderer.draw(shape);
	}
	if(mColor3 != mLocks.end())
	{
		shape.setSize(sf::Vector2f(mCol3.width, mCol3.width));
		shape.setPosition(getX() + mCol3.left, getY() + mCol3.top);
		shape.setFillColor(*mColor3);
		renderer.draw(shape);
	}
	if(mColor4 != mLocks.end())
	{
		shape.setSize(sf::Vector2f(mCol4.width, mCol4.width));
		shape.setPosition(getX() + mCol4.left, getY() + mCol4.top);
		shape.setFillColor(*mColor4);
		renderer.draw(shape);
	}
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

void Player::logic(Level& level, int delta)
{
	// Call creature logic.
	Creature::logic(level, delta);

	// Do the color cycle information after the player's position is updated.
	if(mCycle == COLORCYCLE_MOVE)
	{
		if(mColorCycleTimer.getTime() >= 5)
		{
			mCol1.left += 0.35f;
			mCol2.top  += 0.35f;
			mCol3.left -= 0.35f;
			mCol4.top  -= 0.35f;
			if(mCol1.left >= PLAYER_SIZE * 0.52f)
			{
				mResetCyclePositions();
				mCycle = COLORCYCLE_SWITCHCOLORS;
			}
			mColorCycleTimer.start();
		}
	}
	else if(mCycle == COLORCYCLE_PAUSE)
	{
		if(mColorCycleTimer.getTime() >= COLOR_CYCLE_TIME_INTERVAL)
		{
			mColorCycleTimer.start();
			mCycle = COLORCYCLE_MOVE;
		}
	}
	else if(mCycle == COLORCYCLE_SWITCHCOLORS)
	{
		if(mLocks.empty())
		{
			mColor4 = mColor3 = mColor2 = mColor1 = mLocks.end();
			return;
		}

		// Adjust the color positions.
		mColor4 = mColor3;
		mColor3 = mColor2;
		mColor2 = mColor1;

		// Increment the initial color position
		static int lock_buffer = 0;
		switch(mLocks.size())
		{
			case 0: break;
			case 1:
			{
				if(mColor1 == mLocks.end())
				{
					if(lock_buffer == 0)
					{
						mColor1 = mLocks.begin();
						lock_buffer = 2;
					}
					else
						lock_buffer--;
				}
				else
					mColor1++;
				break;
			}
			case 2:
			{
				if(mColor1 == mLocks.end())
				{
					if(lock_buffer == 0)
					{
						mColor1 = mLocks.begin();
						lock_buffer = 1;
					}
					else
						lock_buffer--;
				}
				else
					mColor1++;
				break;
			}
			case 3:
			{
				if(mColor1 == mLocks.end())
					mColor1 = mLocks.begin();
				else
					mColor1++;
				break;
			}
			default:
			{
				if(++mColor1 == mLocks.end())
					mColor1 = mLocks.begin();
				break;
			}
		}

		mCycle = COLORCYCLE_PAUSE;
	}
}

const sf::Keyboard::Key PLAYER_ACTION_KEY = sf::Keyboard::Space;
const int Player::PLAYER_ACTION_DISTANCE = 2;
