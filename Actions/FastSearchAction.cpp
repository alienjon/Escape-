///*
// * FastSearchAction.cpp
// *
// *  Created on: Apr 23, 2009
// *      Author: alienjon
// */
//
//#include "FastSearchAction.hpp"
//
//#include "../Entities/Creatures/Enemy.hpp"
//#include "../Engine/Logger.hpp"
//
//FastSearchAction::FastSearchAction(Enemy* creature, int time) : mCreature(creature), mTime(time)
//{
//	// Check to see that a creature was provided.
//	if(!mCreature)
//	{
//		Logger::log("FastSearchAction::FastSearchAction() -> Creature not provided, action will automatically trigger.");
//		mActivated = true;
//		mPerformed = true;
//	}
//}
//
//void FastSearchAction::activate(EnvironmentData& eData)
//{
//	// If the action has not yet been activated, activate it.
//	if(!mActivated)
//	{
//		// Start the timer.
//		mTimer.start();
//
//		// Tell the creature to start fast searching.
//		mCreature->fastSearch();
//
//		// This action is activated.
//		mActivated = true;
//	}
//	// The action is already activated, if the timer has passed the alloted time, the action is complete.
//	else if(mTimer.getTime() >= mTime)
//	{
//		// Stop the creature from searching, the time is up.
//		mCreature->stop();
//
//		// The action is complete.
//		mPerformed = true;
//	}
//}
