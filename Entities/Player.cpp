/*
 * Player.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Player.hpp"

const unsigned int COLOR_CYCLE_TIME_INTERVAL = 1300;
const float PLAYER_SIZE = 50.f;
const float INTERNAL_SIZE = 10.f;
const sf::Color PLAYER_COLOR = sf::Color::Blue;

Player::Player() :
	mAllowInput(true),
	mCycle(COLORCYCLE_MOVE),
	mColor1(mLocks.end()), mColor2(mLocks.end()), mColor3(mLocks.end()), mColor4(mLocks.end())
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves at a normal speed.
    setSpeed(1.0);

    // Start the timer.
    mColorCycleTimer.start();

    // Setup the player's size.
    mShape.AddPoint(0, 0, PLAYER_COLOR);
    mShape.AddPoint(PLAYER_SIZE, 0, PLAYER_COLOR);
    mShape.AddPoint(PLAYER_SIZE, PLAYER_SIZE, PLAYER_COLOR);
    mShape.AddPoint(0, PLAYER_SIZE, PLAYER_COLOR);

    // Configure the internal sizes.
    mResetCyclePositions();
}

void Player::mDie()
{
    // Stop accepting player input.
    mAllowInput = false;

    // Continue dying.
    Creature::mDie();
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

	// Draw the colors.
	if(mColor1 != mLocks.end())
		renderer.Draw(sf::Shape::Rectangle(getX() + mCol1.Left, getY() + mCol1.Top, mCol1.Width, mCol1.Height, *mColor1));
	if(mColor2 != mLocks.end())
		renderer.Draw(sf::Shape::Rectangle(getX() + mCol2.Left, getY() + mCol2.Top, mCol2.Width, mCol2.Height, *mColor2));
	if(mColor3 != mLocks.end())
		renderer.Draw(sf::Shape::Rectangle(getX() + mCol3.Left, getY() + mCol3.Top, mCol3.Width, mCol3.Height, *mColor3));
	if(mColor4 != mLocks.end())
		renderer.Draw(sf::Shape::Rectangle(getX() + mCol4.Left, getY() + mCol4.Top, mCol4.Width, mCol4.Height, *mColor4));
}

void Player::keyPressed(gcn::KeyEvent& event)
{
	// Check for allowing input.
    if(!mAllowInput)
        return;

    // Calculate the velocity.
	if(event.getKey().getValue() == gcn::Key::UP)
		mUp = true;
	if(event.getKey().getValue() == gcn::Key::DOWN)
		mDown = true;
	if(event.getKey().getValue() == gcn::Key::LEFT)
		mLeft = true;
	if(event.getKey().getValue() == gcn::Key::RIGHT)
		mRight = true;
}

void Player::keyReleased(gcn::KeyEvent& event)
{
	if(event.getKey().getValue() == gcn::Key::UP)
		mUp = false;
	if(event.getKey().getValue() == gcn::Key::DOWN)
		mDown = false;
	if(event.getKey().getValue() == gcn::Key::LEFT)
		mLeft = false;
	if(event.getKey().getValue() == gcn::Key::RIGHT)
		mRight = false;
}

void Player::logic(Level& level)
{
	// Call creature logic.
	Creature::logic(level);

	// Do the color cycle information after the player's position is updated.
	if(mCycle == COLORCYCLE_MOVE)
	{
		if(mColorCycleTimer.getTime() >= 5)
		{
			mCol1.Left += 0.35f;
			mCol2.Top  += 0.35f;
			mCol3.Left -= 0.35f;
			mCol4.Top  -= 0.35f;
			if(mCol1.Left >= PLAYER_SIZE * 0.52f)
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
				if(++mColor1 == mLocks.end())
					mColor1 = mLocks.begin();
		}

		mCycle = COLORCYCLE_PAUSE;
	}
}

const sf::Keyboard::Key PLAYER_ACTION_KEY = sf::Keyboard::Space;
const int Player::PLAYER_ACTION_DISTANCE = 2;
