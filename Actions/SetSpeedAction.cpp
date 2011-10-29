/*
 * SetSpeedAction.cpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */

#include "SetSpeedAction.hpp"

#include "../Entities/Creature.hpp"
#include "../Engine/Logger.hpp"

SetSpeedAction::SetSpeedAction(Creature& creature, double speed) : mCreature(&creature), mSpeed(speed)
{
	// Check to see that a creature was provided.
	if(!mCreature)
	{
		Logger::log("SetSpeedAction::SetSpeedAction() -> Creature not provided, action will automatically trigger.");
		mActivated = true;
		mPerformed = true;
	}
}

SetSpeedAction::~SetSpeedAction()
{
}

void SetSpeedAction::activate(EnvironmentData& eData)
{
	// If the action has not been activated, then activate it.
	if(!mActivated)
	{
		// If the creature exists, set its speed.
		if(mCreature)
		{
			mCreature->setSpeed(mSpeed);
		}

		// The action is now both activated and performed.
		mActivated = true;
		mPerformed = true;
	}
}
