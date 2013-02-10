/*
 * TimeChangeListener.hpp
 *
 *  Created on: Nov 29, 2011
 *      Author: alienjon
 */
#ifndef TIMECHANGELISTENER_HPP_
#define TIMECHANGELISTENER_HPP_

class TimeChangeListener
{
	public:
	virtual ~TimeChangeListener() {}

	/**
	 * @brief Change the time of a timer.
	 * @param time The time to change (positive adds time, negative subtracts time).
	 */
	virtual void timeChange(int time) = 0;
};

#endif /* TIMECHANGELISTENER_HPP_ */
