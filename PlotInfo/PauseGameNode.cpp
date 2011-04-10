/*
 * PauseGameNode.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: the-saint
 */

#include "PauseGameNode.hpp"

using std::string;

PauseGameNode::PauseGameNode(const string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, unsigned int duration) : PlotNode(keyword, activate, deactivate),
	mDuration(duration)
{
}

void PauseGameNode::activate()
{
	// Start the timer if the duration is greater than 0 then start the timer.
	if(mDuration > 0)
	{
		mTimer.start();
	}

	// Pause gameplay.
	pushEvent(EVENT_PAUSE, "");
}

void PauseGameNode::deactivate()
{
	// Resume gameplay.
	pushEvent(EVENT_UNPAUSE, "");
}

bool PauseGameNode::logic()
{
	// If the timer was started then we are counting to a duration, check it.
	if(mTimer.isStarted() && mTimer.getTime() >= mDuration)
	{
		// Done!
		mIsPerformed = true;
	}

	return mIsPerformed;
}
