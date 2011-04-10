/*
 * MovementListener.hpp
 *
 *  Created on: Jul 20, 2010
 *      Author: the-saint
 */

#ifndef MOVEMENTLISTENER_HPP_
#define MOVEMENTLISTENER_HPP_

class Entity;

/**
 * @brief A movement listener is an object that listens for when entities move.
 */
class MovementListener
{
	public:
	/**
	 * @brief An entity has moved.
	 * @param entity The entity that moved.
	 */
	virtual void entityMoved(Entity& entity) = 0;
};

#endif /* MOVEMENTLISTENER_HPP_ */
