/*
 * DebugNode.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: the-saint
 */

#include "DebugNode.hpp"

#include "../Engine/Logger.hpp"

using std::string;

DebugNode::DebugNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& message) : PlotNode(keyword, activation, deactivation),
	mMessage(message)
{
}

void DebugNode::activate()
{
	// Display the data.
	Logger::log("Debug Node(" + mKeyword + ") -> activation(" + mActivationKeyword + "), deactivation(" + mDeactivationKeyword + ") : " + mMessage);
	mDistributePlotEvent();
	mIsPerformed = true;
}
