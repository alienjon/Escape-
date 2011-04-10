/*
 * RemoveEntityNode.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: the-saint
 */
#include "RemoveEntityNode.hpp"

#include "../Managers/PlotManager.hpp"

using std::string;

RemoveEntityNode::RemoveEntityNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& remove) : PlotNode(keyword, activation, deactivation),
	mRemove(remove)
{
}

void RemoveEntityNode::activate()
{
	// Remove the creature (entity).
	pushEvent(EVENT_ENTITY_REMOVE, mRemove);

	// Activated and performed.
	mIsActivated = mIsPerformed = true;
	mDistributePlotEvent();
}
