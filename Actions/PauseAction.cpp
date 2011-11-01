/*
 * PauseAction.cpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */
#include "PauseAction.hpp"

PauseAction::PauseAction(unsigned int time) : mTime(time)
{
}

void PauseAction::activate(Level& level)
{
	// If the pause action has not been activated yet, then activate it.
	if(!mActivated)
	{
	    // Start the timer.
	    mTimer.start();

		// This action is now activated.
		mActivated = true;
	}

	// If the timer has reached the right time, then the action is complete.
	if(mTimer.getTime() >= mTime)
	{
	    // All done!
	    mPerformed = true;
	}
}
