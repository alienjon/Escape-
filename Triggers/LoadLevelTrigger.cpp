///*
// * LoadLevelTrigger.cpp
// *
// *  Created on: Aug 12, 2009
// *      Author: alienjon
// */
//
//#include "LoadLevelTrigger.hpp"
//
//#include <stdexcept>
//
//#include "../Entities/Entity.hpp"
//#include "../Game/EnvironmentData.hpp"
//#include "../Actions/LoadLevelAction.hpp"
//
//using std::invalid_argument;
//using std::runtime_error;
//using std::string;
//
//LoadLevelTrigger::LoadLevelTrigger(Level* level, Entity* trigger, Entity* player) : mTrigger(trigger),
//																					mPlayer(player)
//{
//    // This is a next level trigger.
//    mType = TRIGGERTYPE_LEVEL_NEXT;
//
//    if(!level)
//    {
//    	throw invalid_argument("NextLevelTrigger() -> Null level.");
//    }
//
//    if(!mTrigger)
//    {
//        throw invalid_argument("NextLevelTrigger::NextLevelTrigger() -> Null trigger provided.");
//    }
//
//    if(!mPlayer)
//    {
//        throw invalid_argument("NextLevelTrigger::NextLevelTrigger() -> Null player provided.");
//    }
//
//    // Set this as a listener for the trigger.
//    mTrigger->addInteractionListener(this);
//
//    // Add the load next level action.
//    addAction(new LoadNextLevelAction(level));
//}
//
//LoadLevelTrigger::LoadLevelTrigger(Level* level, const string& data)
//{
//    // This is a next level trigger.
//    mType = TRIGGERTYPE_LEVEL_NEXT;
//
//    if(!level)
//    {
//    	throw invalid_argument("PreviousLevelTrigger() -> Null level.");
//    }
//
//    /*
//     * Load the trigger in the following manner:
//     * 1) Trigger id
//     * 2) Player id
//     */
////    string::size_type pos = 0;
//    // @todo Need to review loading games
////    mTrigger = level->getEntityById(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
////    mPlayer = level->getEntityById(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//
//    if(!mTrigger || !mPlayer)
//    {
//        throw runtime_error("NextLevelTrigger::NextLevelTrigger() -> Trigger or Player not found.");
//    }
//
//    // Set this as a listener for the trigger.
//    mTrigger->addInteractionListener(this);
//
//    // Add the load next level action.
//    addAction(new LoadNextLevelAction(level));
//}
//
//LoadLevelTrigger::~LoadLevelTrigger()
//{
//    // Unset this as a listener.
//    mTrigger->removeInteractionListener(this);
//}
//
//void LoadLevelTrigger::draw(Renderer& renderer)
//{
//}
//
//string LoadLevelTrigger::extract() const
//{
//    /*
//     * Store the trigger in the following manner:
//     * 1) Trigger id
//     * 2) Player id
//     */
//    return toString(mTrigger->getId()) + CHAR_DELIMITER + toString(mPlayer->getId());
//}
//
//void LoadLevelTrigger::interactionOccurred(Entity* actor, Entity* interactor)
//{
//    // If the being that interacted with the trigger is the player, then go to the next level.
//    if(actor == mPlayer && interactor == mTrigger)
//    {
//        mTripped = true;
//    }
//}
//
//void LoadLevelTrigger::logic(EnvironmentData& eData)
//{
//    // Nothing to do.
//}
