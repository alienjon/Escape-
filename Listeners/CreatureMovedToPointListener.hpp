/*
 * CreatureMovedToPointListener.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */

#ifndef CREATUREMOVEDTOPOINTLISTENER_HPP_
#define CREATUREMOVEDTOPOINTLISTENER_HPP_

#include <list>

class Creature;

/**
 * @brief An interface for when a creature has moved to a point.
 */
class CreatureMovedToPointListener
{
    public:
    /**
     * @brief The creature has moved.
     * @param creature The creature that moved.
     */
    virtual void creatureMoved(Creature& creature) = 0;
};

#endif /* CREATUREMOVEDTOPOINTLISTENER_HPP_ */
