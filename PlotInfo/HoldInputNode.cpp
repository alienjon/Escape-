/*
 * HoldInputNode.cpp
 *
 *  Created on: Aug 5, 2010
 *      Author: the-saint
 */
#include "HoldInputNode.hpp"

using std::string;

HoldInputNode::HoldInputNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation) : PlotNode(keyword, activation, deactivation)
{
}

void HoldInputNode::activate()
{
	pushEvent(EVENT_INPUT_DEACTIVATE, "");
}

void HoldInputNode::deactivate()
{
	pushEvent(EVENT_INPUT_ACTIVATE, "");
}
