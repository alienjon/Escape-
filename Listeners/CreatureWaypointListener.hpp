/*
 * CreatureWaypointListener.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */
#ifndef CREATUREWAYPOINTLISTENER_HPP_
#define CREATUREWAYPOINTLISTENER_HPP_

class Creature;

/**
 * @brief An interface for when a creature has moved to a point.
 */
class CreatureWaypointListener
{
    public:
    /**
     * @brief The creature has moved to a waypoint.
     * @param creature The creature that moved.
     */
    virtual void creatureMoved(Creature& creature) = 0;
};

#endif /* CREATUREWAYPOINTLISTENER_HPP_ */
