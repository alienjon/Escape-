/*
 * DeathListener.hpp
 *
 *  Created on: Aug 5, 2009
 *      Author: alienjon
 */
#ifndef DEATHLISTENER_HPP_
#define DEATHLISTENER_HPP_

class Entity;

/**
 * @brief An interface for an object to listen for when an entity dies.
 */
class DeathListener
{
    public:
    /**
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    virtual void deathOccurred(Entity& entity) = 0;
};

#endif /* DEATHLISTENER_HPP_ */
