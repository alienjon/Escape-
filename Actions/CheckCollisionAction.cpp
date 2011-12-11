/*
 * CheckCollisionAction.cpp
 *
 *  Created on: Dec 11, 2011
 *      Author: alienjon
 */
#include "CheckCollisionAction.hpp"

#include "../Entities/Entity.hpp"
#include "../Game/Level.hpp"

CheckCollisionAction::CheckCollisionAction(Entity& entity) :
	mEntity(entity)
{
}

void CheckCollisionAction::activate(Level& level)
{
	level.checkEntityCollision(mEntity);
	mPerformed = true;
}
