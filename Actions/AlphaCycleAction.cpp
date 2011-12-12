/*
 * AlphaCycleAction.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#include "AlphaCycleAction.hpp"

#include <stdexcept>

#include "../Entities/Creature.hpp"
#include "../Entities/Entity.hpp"

AlphaCycleAction::AlphaCycleAction(Entity& entity) :
	mEntity(entity),
	mIncreaseAlpha(false),
	mOriginalAlpha(255)
{
}

AlphaCycleAction::~AlphaCycleAction()
{
	Creature* creature = dynamic_cast<Creature*>(&mEntity);
	if(!creature)
		throw std::runtime_error("Invalid conversion to Creature.");
	creature->removeCreatureWaypointListener(this);
}

void AlphaCycleAction::activate(Level& level)
{
	if(!mActivated)
	{
		mActivated = true;
		mTimer.start();
		mOriginalAlpha = mEntity.getAlpha();
		if(mEntity.getAlpha() == 0)
			mIncreaseAlpha = true;
	}

	if(mTimer.isStarted() && mTimer.getTime() >= 5)
	{
		if(mIncreaseAlpha)
			mEntity.setAlpha(mEntity.getAlpha() + 5);
		else
			mEntity.setAlpha(mEntity.getAlpha() - 5);
		mTimer.start();
	}
}

void AlphaCycleAction::creatureMoved(Creature& creature)
{
	if(&creature == &mEntity)
	{
		mEntity.setAlpha(mOriginalAlpha);
		mPerformed = true;
	}
}
