/*
 * WalkToNode.cpp
 *
 *  Created on: Aug 5, 2010
 *      Author: the-saint
 */
#include "WalkToNode.hpp"

#include "../Entities/Creatures/Creature.hpp"
#include "../main.hpp"

using std::string;

WalkToNode::WalkToNode(const string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, const string& name, const Vector& point) : PlotNode(keyword, activate, deactivate),
	mName(name),
	mPoint(point),
	mCreature(0)
{
}

WalkToNode::~WalkToNode()
{
	// Make sure this is removed as a listener.
	if(mCreature)
	{
		mCreature->removeCreatureMovedToPointListener(this);
	}
}

void WalkToNode::activate()
{
	// Pass a creature walk event.
	pushEvent(EVENT_CREATURE_WALKTO, mName + ":" + toString(mPoint.x) + ":" + toString(mPoint.y), this);
}

void WalkToNode::creatureMoved(Creature& creature)
{
    if(!mIsPerformed && creature.getName() == mName && creature.getX() == mPoint.x && creature.getY() == mPoint.y)
    {
        // The creature has finished moving to its location, deactivate.
    	mIsPerformed = true;
    	mDistributePlotEvent();
    	mCreature = &creature;
    }
}
