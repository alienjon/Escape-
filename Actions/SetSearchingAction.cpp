/*
 * SetSearchingAction.cpp
 *
 *  Created on: May 2, 2009
 *      Author: alienjon
 */
#include "SetSearchingAction.hpp"

#include "../Entities/Creatures/Creature.hpp"
#include "../Engine/Logger.hpp"

SetSearchingAction::SetSearchingAction(Creature& creature, bool state) :
	mCreature(creature),
    mState(state)
{
}

void SetSearchingAction::activate(EnvironmentData& eData)
{
    // Set the searching state.
    mCreature.setSearching(mState);

    // Action now performed.
    mActivated = true;
    mPerformed = true;
}
