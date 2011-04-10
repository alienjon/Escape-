/*
 * MessageNode.cpp
 *
 *  Created on: Jul 19, 2010
 *      Author: the-saint
 */
#include "MessageNode.hpp"

#include "../Managers/PlotManager.hpp"

using std::string;

MessageNode::MessageNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& title, const string& message) : PlotNode(keyword, activation, deactivation),
	mTitle(title),
	mMessage(message)
{
}

void MessageNode::activate()
{
	// Add the message.
	PlotManager::mAddMessage(mTitle, mMessage);

	// The node is immediately completed.
	mDistributePlotEvent();

	// Performed.
	mIsPerformed = true;
}
