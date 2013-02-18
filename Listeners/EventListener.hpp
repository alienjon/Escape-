/*
 * EventListener.hpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

#include <string>

/**
 * @brief A listener for events between classes.
 */
class EventListener
{
	public:
	virtual ~EventListener() {}

	/**
	 * @brief An event occurred.
	 * @param eventId The event's ID.
	 */
	virtual void eventOccurred(const std::string& eventId) = 0;
};

#endif /* EVENTLISTENER_HPP_ */
