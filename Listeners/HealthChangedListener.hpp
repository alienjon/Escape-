/*
 * HealthChangedListener.hpp
 *
 *  Created on: Aug 5, 2009
 *      Author: alienjon
 */

#ifndef HEALTHCHANGEDLISTENER_HPP_
#define HEALTHCHANGEDLISTENER_HPP_

class Entity;

/**
 * @brief An interface for when a creature's health has changed.
 */
class HealthChangedListener
{
    public:
    /**
     * @brief The health changed.
     * @param entity The entity whose health changed.
     */
    virtual void healthChanged(Entity* entity) = 0;
};

#endif /* HEALTHCHANGEDLISTENER_HPP_ */
