/***************************************************************************
 *   Copyright (C) 2007 by Jonathan Rosen   *
 *   holy.smoking.floorboards.batman@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "Timer.hpp"

#include "../main.hpp"

Timer::Timer() : mCurrentTime(0),
                 mPausedTime(0),
                 mRunning(false),
                 mPaused(false)
{
}

void Timer::start()
{
	mRunning = true;
	mPaused = false;
	mCurrentTime = SDL_GetTicks();
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

void Timer::pause()
{
	// Only pause the timer if the timer is already running and isn't already paused.
	if(mRunning && !mPaused)
	{
		mPaused = true;
		mPausedTime = SDL_GetTicks() - mCurrentTime;
	}
}

void Timer::unpause()
{
	if(mPaused)
	{
		// Unpause the timer.
		mPaused = false;
		mCurrentTime = SDL_GetTicks() - mPausedTime;
		mPausedTime = 0;
	}
}

bool Timer::isStarted() const
{
	return mRunning;
}

bool Timer::isPaused() const
{
	return mPaused;
}

unsigned int Timer::getTime() const
{
	// If the timer is running, return a determined time.
	if(mRunning)
	{
		// If the timer is paused, return the time the timer was paused at.
		if(mPaused)
		{
			return mPausedTime;
		}
		else
		{
			return SDL_GetTicks() - mCurrentTime;
		}
	}
	// If the timer is not running, return 0.
	else
	{
		return 0;
	}
}
