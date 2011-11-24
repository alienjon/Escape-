///*
// * SetWanderAction.cpp
// *
// *  Created on: Aug 7, 2009
// *      Author: alienjon
// */
//#include "SetWanderAction.hpp"
//
//#include "../Entities/Creature.hpp"
//
//#include <stdexcept>
//
//using std::invalid_argument;
//
//SetWanderAction::SetWanderAction(Creature* creature, bool state) :
//	mCreature(creature),
//    mState(state)
//{
//    // Make sure the creature exists.
//    if(!mCreature)
//    {
//        throw invalid_argument("SetWanderAction() -> No creature provided.");
//    }
//}
//
//void SetWanderAction::activate(Level& level)
//{
//    // Set the creature's wandering state.
////    mCreature->setWandering(mState);@todo review
//
//    // Done!
//    mPerformed = true;
//}
