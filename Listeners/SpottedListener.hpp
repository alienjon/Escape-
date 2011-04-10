/*
 * SpottedListener.hpp
 *
 *  Created on: Jul 14, 2009
 *      Author: alienjon
 */

#ifndef SPOTTEDLISTENER_HPP_
#define SPOTTEDLISTENER_HPP_

#include "../Events/SpottedEvent.hpp"

/**
 * @brief A spotted listener is an object who listens for when an enemy spots a victim.
 */
class; SpottedListener
{
    /**
     * @brief A victim was spotted.
     * @param event The event detailing the spotting.
     */
    virtual void victimSpotted(SpottedEvent event) = 0;
};

#endif /* SPOTTEDLISTENER_HPP_ */
