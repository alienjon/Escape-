/*
 * EventInterface.hpp
 *
 *  Created on: May 20, 2010
 *      Author: the-saint
 */

#ifndef EVENTINTERFACE_HPP_
#define EVENTINTERFACE_HPP_

#include <list>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Listeners/EventListener.hpp"

class EventInterface
{
	public:
    /**
     * @brief Add an event listener.
     * @param listener The listener to add.
     */
    virtual void addEventListener(EventListener* listener);

    /**
     * @brief Push an event to the listeners.
     * @param event The event to push.
     * @param content Additional content.
     * @param node Some events have an associated plot node.
     */
    virtual void pushEvent(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    /**
     * @brief Remove an event listener.
     * @param listener The listener to remove.
     */
    virtual void removeEventListener(EventListener* listener);

	protected:
    /**
     * @brief Hidden constructor.
     */
    EventInterface();

    /**
     * The event listeners.
     */
    std::list<EventListener*> mEventListeners;
};

#endif /* EVENTINTERFACE_HPP_ */
