/*
 * SetCollidableAction.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#include "SetCollidableAction.hpp"

SetCollidableAction::SetCollidableAction(Entity& entity, bool state) :
	mEntity(entity),
	mState(state)
{
}

void SetCollidableAction::activate(Level& level)
{
	mEntity.setCollidable(mState);
	mActivated = true;
	mPerformed = true;
}
