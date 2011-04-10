/*
 * CreatureConfigNode.cpp
 *
 *  Created on: Aug 12, 2010
 *      Author: the-saint
 */
#include "CreatureConfigNode.hpp"

using std::string;

CreatureConfigNode::CreatureConfigNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& data) : PlotNode(keyword, activation, deactivation),
	mData(data)
{
}

void CreatureConfigNode::activate()
{
	// Push the event.
	pushEvent(EVENT_CREATURE_CONFIG, mData);

	// The node is now performed.
	mIsPerformed = true;

	// All done!
	mDistributePlotEvent();
}
