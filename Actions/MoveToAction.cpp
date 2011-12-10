/*
 * MoveToAction.cpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */
#include "MoveToAction.hpp"

#include "../Entities/Creature.hpp"
#include "../Engine/Logger.hpp"

MoveToAction::MoveToAction(Creature& creature, const sf::Vector2f& loc) :
	mCreature(creature),
    mLoc(loc)
{
}

MoveToAction::~MoveToAction()
{
    // Remove this as a listener for the creature.
    mCreature.removeCreatureWaypointListener(this);
}

void MoveToAction::activate(Level& level)
{
    // If the action was not activated, the creature was not provided a direction to face.
    if(!mActivated)
    {
        // Tell the creature to move to the point.
        mCreature.setWaypoint(mLoc);

        // Start listening to that creature for when it has moved to the point.
        mCreature.addCreatureWaypointListener(this);

        // Action activated.
        mActivated = true;
    }
}

void MoveToAction::creatureMoved(Creature& creature)
{
    if(&creature == &mCreature)
        mPerformed = true;
}
