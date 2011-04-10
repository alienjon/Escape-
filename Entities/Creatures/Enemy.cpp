///*
// * Enemy.cpp
// *
// *  Created on: Apr 2, 2009
// *      Author: alienjon
// */
//
//#include "Enemy.hpp"
//
//#include "Player.hpp"
//
//#include "../../Actions/Action.hpp"
//#include "../../Managers/AnimationManager.hpp"
//#include "../Entity.hpp"
//#include "../../Engine/Colors.hpp"
//#include "../../Actions/DisplayAnimationAction.hpp"
//#include "../../Game/EnvironmentData.hpp"
//#include "../../Actions/FastSearchAction.hpp"
//#include "../../Game/Level.hpp"
//#include "../../Engine/Logger.hpp"
//#include "../../Actions/MoveToAction.hpp"
//#include "../../Actions/MultipleActionsAction.hpp"
//#include "../../Managers/ObjectManager.hpp"
//#include "../../Actions/PauseAction.hpp"
//#include "../../Math/Point.hpp"
//#include "../../Math/Quadrilateral.hpp"
//#include "../../Engine/Renderer.hpp"
//#include "../../Actions/SetSearchingAction.hpp"
//#include "../../Actions/SetSpeedAction.hpp"
//#include "../../Actions/SlideAction.hpp"
//#include "../../Actions/WanderAction.hpp"
//
//Enemy::Enemy() : mIsSearching(true),
//                 mFastSearchTime(0),
//                 mDefaultSpeed(0.66),
//                 mChasingSpeed(2.0)
//{
//	// Set the default speed.
//	setSpeed(mDefaultSpeed);
//
//    // Generate the initial search areas, now that the animations have been set.
//    mGenerateSearchArea(mFacingDirection);
//}
//
//void Enemy::mCreatureInteract(Entity* object)
//{
//    object->interact(this);
//}
//
//void Enemy::mDied()
//{
//    // Call creature died.
//    Creature::mDied();
//
//    // Additionally, stop searching.
//    setSearching(false);
//}
//
//void Enemy::mPushedActions(Direction dir)
//{
//    // Pause for a moment.
//    addAction(new PauseAction(1000));
//
//    // Fast search for a bit.
//    addAction(new FastSearchAction(this, 10000));
//
//    // If the creature was pushed, I also want to have the creature start searching again.
//    addAction(new SetSearchingAction(this, true));
//
//    // Make sure we're back to default speed.
//    addAction(new SetSpeedAction(*this, mDefaultSpeed));
//
//    // After being pushed back, start searching again if necessary.
//    if(isWandering())
//    {
//        addAction(new WanderAction(this));
//    }
//
//    // If there's currently a victim this enemy is attacking, then stop fighting it.
//    if(mVictim)
//    {
//        // Stop fighting.
//        mVictim->stopFighting(this);
//        stopFighting(mVictim);
//    }
//}
//
//void Enemy::mRunOverTo(Entity& being)
//{
//    // If we are showing point found locations, add this point.
//    if(Game::isDebug())
//    {
//// @todo How do I want to implement GUI interaction?        mLevel->addMarker(being.getDimension().getCenterPoint());
//    }
//
//    // Stop searching.
//    mFastSearchTimer.stop();
//
//    // I need to pause the enemy, indicate that the enemy saw the player and speed up the creature.
//    ActionList* actions = new ActionList;
//    actions->push_back(new SetSearchingAction(this, false));
//    actions->push_back(new SetSpeedAction(*this, mChasingSpeed));
//    addAction(new MultipleActionsAction(actions));
//
//    // Run over to the spot the player was just at.
//    addAction(new MoveToAction(this, being.getDimension().getCenterPoint()));
//
//    // Continue searching.
//    addAction(new SetSearchingAction(this, true));
//
//    // Enable fast searching for a little bit.
//    addAction(new FastSearchAction(this, 10000));
//
//    // Slow the creature back down.
//    addAction(new SetSpeedAction(*this, mDefaultSpeed));
//
//    // Resume wandering, if wandering.
//    if(isWandering())
//    {
//        addAction(new WanderAction(this));
//    }
//}
//
//void Enemy::attack(Creature* creature)
//{
//    // Clear any actions.
//    clearActions();
//
//    // Face the creature.
//    mSetStopAnimation(directionToPoint(getDimension().getCenterPoint(), creature->getDimension().getCenterPoint()));
//
//    // Start the timer and randomize the next time the creature will be attacked.
//    mAttackTimer.start();
//    mAttackTimerCounter = 0;
//
//    // Set the victim.
//    mVictim = creature;
//
//    // Start listening to the creature for when it dies.
//    creature->addDeathListener(this);
//
//    // Stop searching for someone to attack.  We've found someone!
//    setSearching(false);
//}
//
//void Enemy::draw(Renderer& renderer)
//{
//    if(Game::isDebug())
//    {
//        renderer.setColor(COLOR_BLUE);
//        renderer.fillQuadrilateral(mGetSearchArea(0, 0));
//    }
//    Creature::draw(renderer);
//}
//
//void Enemy::fastSearch()
//{
//    // Stop all movements.
//    // @note This must go before setting fast search to true, as stop() will also stop fast searching.
//    stop();
//
//    // Additionally, perform regular searching.
//    setSearching(true);
//
//    // Start the timer.
//    mFastSearchTimer.start();
//
//    // Get the initial search number.
//    mFastSearchTime = random(FASTSEARCH_MIN, FASTSEARCH_MAX);
//}
//
//void Enemy::interact(Player* player)
//{
//    // If the Enemy is currently attacking the player then the player is trying to break the attack.
//    if(mVictim)
//    {
//        // The player is trying to push the enemy.
//        push(player->getFacingDirection(), PLAYER_PUSH_FORCE);
//    }
//    // ... if the enemy is not fighting the calling player, then the enemy is stop attacking (if it is) and is pushed
//    else
//    {
//        // Stop everything, I'm being pushed!
//        stop();
//
//        // Push.
//        push(player->getFacingDirection(), PLAYER_PUSH_FORCE * 4);
//    }
//}
//
//void Enemy::logic(EnvironmentData& eData) // @todo an enemy should interact when it bumps into something (it did not stop moving on its own)
//{
//    // If the creature is fast searching, see if it needs to change direction.
//    if(mFastSearchTimer.isStarted() && mFastSearchTimer.getTime() >= mFastSearchTime)
//    {
//    	// Get a random direction.
//    	Direction dir = getDirection(random(0, 7));
//
//    	// Stand in that direction.
//    	mSetStopAnimation(dir);
//
//    	// Restart the timer.
//    	mFastSearchTimer.start();
//
//    	// Set the new search time to be a random number.
//    	mFastSearchTime = random(FASTSEARCH_MIN, FASTSEARCH_MAX);
//    }
//
//	// If the enemy is not sleeping, then check to see if it sees the player.
//	if(mIsSearching)
//	{
//        // If a victim (the player) is inside the search area, then run to the spot it is currently in to attack!
//		// @todo Check victim searching code... is this how I want to do it?
////		Entity* victim = eData.checkEntityCollision(mGetSearchArea(0, 0));
////        if(victim)
////        {
////            clearActions();
////            mRunOverTo(*victim);
////        }
//	}
//
//    // Perform creature logic.
//    Creature::logic(eData);
//}
//
//void Enemy::setSearching(bool state)
//{
//    mIsSearching = state;
//}
//
//void Enemy::stop()
//{
//    // Stop the creature.
//    Creature::stop();
//
//    // Stop fast searching.
//    mFastSearchTimer.stop();
//}
//
//const int Enemy::FASTSEARCH_MIN = 750;
//const int Enemy::FASTSEARCH_MAX = 2000;
