/*
 * EventInterface.hpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#ifndef EVENTINTERFACE_HPP_
#define EVENTINTERFACE_HPP_

#include <list>
#include <string>

#include "../Listeners/EventListener.hpp"

/*
 * @brief An interface for sending signals (events) between classes.
 */
class EventInterface
{
	public:
	/**
	 * @brief Default constructor.
	 */
	EventInterface() {}
	virtual ~EventInterface() {}

    /**
     * @brief Add an event listener.
     * @param listener The listener.
     */
    inline void addEventListener(EventListener* listener)
    {
    	mEventListeners.push_back(listener);
    }

    /**
     * @brief Remove an action listener.
     * @param listener The listener.
     */
    inline void removeEventListener(EventListener* listener)
    {
    	mEventListeners.remove(listener);
    }

	protected:
    /**
     * @brief Distribute event.
     * @param str The event string.
     */
    void distributeEvent(const std::string& str)
    {
    	for(std::list<EventListener*>::const_iterator it(mEventListeners.begin()); it != mEventListeners.end(); ++it)
    		(*it)->eventOccurred(str);
    }

	private:
    // The listeners.
    std::list<EventListener*> mEventListeners;
};

#endif /* ACTIONEVENTINTERFACE_HPP_ */
