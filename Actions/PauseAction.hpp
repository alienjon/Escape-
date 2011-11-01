/*
 * PauseAction.hpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */
#ifndef PAUSEACTION_HPP_
#define PAUSEACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief An action that waits a certain amount of time before it has executed.
 */
class PauseAction : public Action
{
	public:
	/**
	 * @brief A pause action pauses actions for a period of time.
	 * @param time The amount of time (in ms) the to wait.
	 */
	PauseAction(unsigned int time);

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

	private:
	/**
	 * The pause timer.
	 */
	Timer mTimer;

	/**
	 * The length of time to pause the creature (in ms)
	 */
	unsigned int mTime;
};

#endif /* PAUSEACTION_HPP_ */
