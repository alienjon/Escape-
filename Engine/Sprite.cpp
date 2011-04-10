/*
 * Sprite.cpp
 *
 *  Created on: Apr 3, 2009
 *      Author: alienjon
 */
#include "Sprite.hpp"

#include <stdexcept>

#include "../Engine/Logger.hpp"

using std::list;
using std::out_of_range;
using std::runtime_error;
using std::vector;

Sprite::Sprite() :
	mCurrentFrame(0),
	mIsVisible(true)
{
    mAnimationTimer.start();
}

Sprite::Sprite(Surface* surface) :
	mCurrentFrame(0),
	mIsVisible(true)
{
	mAnimationTimer.start();
	mAddFrame(surface);
}

void Sprite::mAddFrame(Surface* surface)
{
	mFrames.push_back(surface);
}

void Sprite::mClearFrames()
{
	mFrames.clear();
}

void Sprite::addAnimationCycleListener(AnimationCycleListener* listener)
{
    mAnimationCycleListeners.push_back(listener);
}

void Sprite::draw(gcn::Graphics* graphics, const Vector& pos)
{
    // Draw the current surface.
	try
	{
		if(mIsVisible)
		{
			graphics->drawImage(mFrames.at(mCurrentFrame), pos.x, pos.y);
		}
	}
	catch(const runtime_error& e)
	{
		Logger::error("Sprite does not have any images.");
	}
}

void Sprite::draw(gcn::Graphics* graphics, const int& x, const int& y)
{
    // Draw the current surface.
	try
	{
		if(mIsVisible)
		{
			graphics->drawImage(mFrames.at(mCurrentFrame), x, y);
		}
	}
	catch(const runtime_error& e)
	{
		Logger::error("Sprite does not have any images.");
	}
}

void Sprite::draw(Renderer& renderer, const Vector& pos)
{
    // Draw the current surface.
	try
	{
		if(mIsVisible)
		{
			renderer.drawImage(mFrames.at(mCurrentFrame), pos.x, pos.y);
		}
	}
	catch(const out_of_range& e)
	{
		throw runtime_error("Sprite does not have any images.");
	}
}

void Sprite::draw(Renderer& renderer, const int& x, const int& y)
{
    // Draw the current surface.
	try
	{
		if(mIsVisible)
		{
			renderer.drawImage(mFrames.at(mCurrentFrame), x, y);
		}
	}
	catch(const runtime_error& e)
	{
		Logger::error("Sprite does not have any images.");
	}
}

unsigned int Sprite::getFrame() const
{
	return mCurrentFrame;
}

int Sprite::getHeight() const
{
    return mFrames.empty() ? 0 : mFrames.at(mCurrentFrame)->getHeight();
}

unsigned int Sprite::getNumberOfFrames() const
{
	return mFrames.size();
}

int Sprite::getWidth() const
{
    return mFrames.empty() ? 0 : mFrames.at(mCurrentFrame)->getWidth();
}

bool Sprite::isAnimating() const
{
    return !mAnimationTimer.isPaused();
}

bool Sprite::isVisible() const
{
    return mIsVisible;
}

void Sprite::logic()
{
	// @todo place pause in sprite if(!mAnimationTimer.isPaused() && (mAnimationTimer.getTime() >= (*mCurrentFrame)->getPause()))
	if(!mAnimationTimer.isPaused() && (mAnimationTimer.getTime() > 100))
	{
		// Go to the next frame.
		mCurrentFrame++;

		// If the next image is out of bounds, then set the current image to the first image.
		if(mCurrentFrame == mFrames.size())
		{
			// Reset the animation.
			mCurrentFrame = 0;

            // Tell the animation cycle listeners that the cycle has finished.
            for(list<AnimationCycleListener*>::iterator it = mAnimationCycleListeners.begin(); it != mAnimationCycleListeners.end(); ++it)
            {
                (*it)->animationCycled();
            }
		}

		// Finally, reset the timer.
		mAnimationTimer.start();
	}
}

void Sprite::removeAnimationCycleListener(AnimationCycleListener* listener)
{
    mAnimationCycleListeners.remove(listener);
}

void Sprite::setAnimating(bool state)
{
	if(state)
	{
		mAnimationTimer.start();
		mCurrentFrame = 0; // Reset to the first frame.
	}
	else
	{
		mAnimationTimer.pause();
	}
}

void Sprite::setFrame(unsigned int frame)
{
	if(frame >= getNumberOfFrames())
	{
		frame = 0;
	}
	mCurrentFrame = frame;
}

void Sprite::setVisible(bool state)
{
    mIsVisible = state;
}
