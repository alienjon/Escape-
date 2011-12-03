/*
 * TimeChangeInterface.hpp
 *
 *  Created on: Nov 29, 2011
 *      Author: alienjon
 */
#ifndef TIMECHANGEINTERFACE_HPP_
#define TIMECHANGEINTERFACE_HPP_

#include <list>

#include "../Listeners/TimeChangeListener.hpp"

class TimeChangeInterface
{
	public:
	/**
	 * @brief Add an TimeChangeListener.
	 * @param listener The listener to add.
	 */
	inline void addTimeChangeListener(TimeChangeListener* listener)
	{
		mTimeChangeListeners.push_back(listener);
	}

	/**
	 * @brief Distribute a time change event.
	 * @param time The time to change.
	 */
	inline void distributeTimeChange(int time)
	{
		for(std::list<TimeChangeListener*>::iterator it = mTimeChangeListeners.begin(); it != mTimeChangeListeners.end(); it++)
			(*it)->timeChange(time);
	}

	/**
	 * @brief Remove an AddLockListener.
	 * @param listener The listener to remove.
	 */
	inline void removeTimeChangeListener(TimeChangeListener* listener)
	{
		mTimeChangeListeners.remove(listener);
	}

	private:
	// The list of TimeChangeListener.
	std::list<TimeChangeListener*> mTimeChangeListeners;
};

#endif /* TIMECHANGEINTERFACE_HPP_ */
