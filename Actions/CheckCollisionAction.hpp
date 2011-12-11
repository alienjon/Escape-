/*
 * CheckCollisionAction.hpp
 *
 *  Created on: Dec 11, 2011
 *      Author: alienjon
 */
#ifndef CHECKCOLLISIONACTION_HPP_
#define CHECKCOLLISIONACTION_HPP_

#include "../Actions/Action.hpp"

class Entity;

/**
 * @brief An action to check for entity collisions.
 * @note To be used to check for interactions between entities.
 */
class CheckCollisionAction : public Action
{
	public:
	/**
	 * @brief Default constructor.
	 * @param entity The entity to check collisions for.
	 */
	CheckCollisionAction(Entity& entity);

	/**
	 * @brief Activate the action.
	 * @param level The level in which the action is acting.
	 */
	virtual void activate(Level& level);

	private:
	// The creature.
	Entity& mEntity;
};

#endif /* CHECKCOLLISIONACTION_HPP_ */
