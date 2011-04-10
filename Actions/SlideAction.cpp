/*
 * SlideAction.cpp
 *
 *  Created on: May 2, 2009
 *      Author: alienjon
 */
#include "SlideAction.hpp"

#include "../Game/EnvironmentData.hpp"

SlideAction::SlideAction(Entity& entity, const Vector& destPt, unsigned int distance) :
	mEntity(entity),
	mDestPoint(destPt),
	mDistance(distance)
{
    // If the distance is equal to zero, then it is already performed.
    if(!mDistance)
    {
    	mPerformed = true;
    }
}

void SlideAction::activate(EnvironmentData& eData)
{
	// Store the old position, get the new position, and set it.
	const Vector old_loc = mEntity.getPosition();
	const Vector new_loc = getVectorOnLine(mEntity.getPosition(), mDestPoint, 1);
	mEntity.setPosition(new_loc.x, new_loc.y);

    // If the creature collides with anything, move back and stop sliding.
    if(!(eData.checkCollision(mEntity).empty()))
    {
        // Reset the old position.
        mEntity.setPosition(old_loc.x, old_loc.y);

        // Done sliding.
        mPerformed = true;
    }

    // I'm one step closer to reaching where I was going.
    mDistance--;

    // If we've arrived, we're done.
    if(mDistance == 0)
    {
        mPerformed = true;
    }
}
