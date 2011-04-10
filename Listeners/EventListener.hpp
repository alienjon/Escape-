/*
 * EventListener.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: alienjon
 */

#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

#include <string>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Game/Event.hpp"

/**
 * @brief A listener for game events.
 */
class EventListener
{
    public:
    /**
     * @brief An event occurred.
     * @param event The game event.
     * @param content Additional content.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creatureMovedToPointListener = 0) = 0;
};

#endif /* EVENTLISTENER_HPP_ */
