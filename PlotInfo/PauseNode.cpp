/*
 * PauseNode.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: the-saint
 */

#include "PauseNode.hpp"

using std::string;

PauseNode::PauseNode(const string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, unsigned int duration) : PlotNode(keyword, activate, deactivate),
	mDuration(duration)
{
}

void PauseNode::activate()
{
	mTimer.start();
}

bool PauseNode::logic()
{
	if(mTimer.getTime() > mDuration)
	{
		mIsPerformed = true;
	}

	return mIsPerformed;
}
