/*
 * PlayerInteractionListener.hpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */

#ifndef PLAYERINTERACTIONLISTENER_HPP_
#define PLAYERINTERACTIONLISTENER_HPP_

class Entity;

/**
 * @brief An interface for when an entity interacts with another entity.
 */
class InteractionListener
{
    public:
    /**
     * @brief A entity was interacted with.
     * @param actor The acting entity.
     * @param interacter The entity being interacted with.
     */
    virtual void interactionOccurred(Entity* actor, Entity* interacter) = 0;
};

#endif /* PLAYERINTERACTIONLISTENER_HPP_ */
