/*
 * GoToNode.cpp
 *
 *  Created on: Jul 20, 2010
 *      Author: the-saint
 */
#include "GoToNode.hpp"

#include "../Game/Event.hpp"
#include "../main.hpp"

using std::string;

GoToNode::GoToNode(const string& keyword, const NodeKeywordSet& activation, const string& level, const Vector& location) : PlotNode(keyword, activation, NodeKeywordSet()),
	mLevel(level),
	mLocation(location)
{
}

void GoToNode::activate()
{
	// If the node hasn't been performed yet, then move the object to the desired location in the desired level.
	if(!mIsPerformed)
	{
		pushEvent(EVENT_GOTO, mLevel + CHAR_DELIMITER + toString(mLocation.x) + CHAR_DELIMITER + toString(mLocation.y));
	}

	// Deactivate.
	mDistributePlotEvent();
	mIsPerformed = true;
}
