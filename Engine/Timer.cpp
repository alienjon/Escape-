/*
 * Timer.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: alienjon
 */
#include "Timer.hpp"

Timer::Timer() :
	mCurrentTime(0),
	mPausedTime(0),
	mRunning(false),
	mPaused(false)
{
}

unsigned int Timer::getTime() const
{
	// If the timer is running, return a determined time.
	if(mRunning)
	{
		// If the timer is paused, return the time the timer was paused at.
		if(mPaused)
			return mPausedTime;
		else
			return mClock.GetElapsedTime() - mCurrentTime;
	}
	// If the timer is not running, return 0.
	else
		return 0;
}

bool Timer::isPaused() const
{
	return mPaused;
}

bool Timer::isStarted() const
{
	return mRunning;
}

void Timer::pause()
{
	// Only pause the timer if the timer is already running and isn't already paused.
	if(mRunning && !mPaused)
	{
		mPaused = true;
		mPausedTime = mClock.GetElapsedTime() - mCurrentTime;
	}
}

void Timer::start()
{
	mRunning = true;
	mPaused = false;
	mCurrentTime = mClock.GetElapsedTime();
}

void Timer::stop()
{
	// Only stop the timer if it isn't already stopped.
	if(mRunning)
	{
		mRunning = false;
		mPaused = false;
	}
}

void Timer::unpause()
{
	if(mPaused)
	{
		// Unpause the timer.
		mPaused = false;
		mCurrentTime = mClock.GetElapsedTime() - mPausedTime;
		mPausedTime = 0;
	}
}
