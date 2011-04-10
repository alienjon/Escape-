///*
// * FastSearchAction.hpp
// *
// *  Created on: Apr 23, 2009
// *      Author: alienjon
// */
//
//#ifndef FASTSEARCHACTION_HPP_
//#define FASTSEARCHACTION_HPP_
//
//#include "Action.hpp"
//#include "../Engine/Timer.hpp"
//
//class Enemy;
//
///**
// * @brief An action to tell an enemy to fast search for a certain amount of time.
// */
//class FastSearchAction : public Action
//{
//	public:
//	/**
//	 * @brief Tell a specified creature to perform a 'fast search' for a specified amount of time.
//	 * @param creature The creature to have search.
//	 * @param time The amount of time to search (after which, stop is called)
//	 */
//	FastSearchAction(Enemy* creature, int time);
//
//    /**
//     * @brief Activate the action.
//     * @param eData The environment data.
//     */
//    virtual void activate(EnvironmentData& eData);
//
//	protected:
//	/**
//	 * The creature.
//	 */
//	Enemy* mCreature;
//
//	/**
//	 * The timer.
//	 */
//	Timer mTimer;
//
//	/**
//	 * The time to count to.
//	 */
//	uint mTime;
//};
//
//#endif /* FASTSEARCHACTION_HPP_ */
