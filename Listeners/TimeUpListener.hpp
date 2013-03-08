/*
 * TimeUpListener.hpp
 *
 *  Created on: Mar 7, 2013
 *      Author: alienjon
 */
#ifndef TIMEUPLISTENER_HPP_
#define TIMEUPLISTENER_HPP_

/**
 * @brief Respond to when a timer has hit zero.
 */
class TimeUpListener
{
	public:
	virtual ~TimeUpListener() {}

	/**
	 * @brief A timer has run out of time.
	 */
	virtual void timeUp() = 0;
};

#endif /* TIMEUPLISTENER_HPP_ */
