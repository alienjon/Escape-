/*
 * WanderAction.cpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */

#include "WanderAction.hpp"

#include "../Entities/Creature.hpp"
#include "../Engine/Logger.hpp"

WanderAction::WanderAction(Creature* creature) : mCreature(creature)
{
	// Check to see that a creature was provided.
	if(!mCreature)
	{
		Logger::log("WanderAction::WanderAction() -> Creature not provided, action will automatically trigger.");
		mActivated = true;
		mPerformed = true;
	}
}

WanderAction::~WanderAction()
{
}

void WanderAction::activate(EnvironmentData& eData)
{
	// Tell the creature to wander.
	if(mCreature)
	{
//		mCreature->wander(); @todo review
	}

	// The action is activated and performed.
	mActivated = true;
	mPerformed = true;
}
