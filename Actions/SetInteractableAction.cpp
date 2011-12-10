/*
 * SetInteractableAction.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#include "SetInteractableAction.hpp"

SetInteractableAction::SetInteractableAction(Entity& entity, bool state) :
	mEntity(entity),
	mState(state)
{
}

void SetInteractableAction::activate(Level& level)
{
	mEntity.setInteractable(mState);
	mActivated = true;
	mPerformed = true;
}
