/*
 * EventInterface.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: the-saint
 */
#include "EventInterface.hpp"

EventInterface::EventInterface()
{}

void EventInterface::addEventListener(EventListener* listener)
{
	mEventListeners.push_back(listener);
}

void EventInterface::pushEvent(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	for(std::list<EventListener*>::iterator it = mEventListeners.begin(); it != mEventListeners.end(); ++it)
	{
		(*it)->eventOccurred(event, content, creatureMovedToPointListener);
	}
}

void EventInterface::removeEventListener(EventListener* listener)
{
	mEventListeners.remove(listener);
}
