/*
 * SetCollidableAction.hpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#ifndef SETCOLLIDABLEACTION_HPP_
#define SETCOLLIDABLEACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Entities/Entity.hpp"

/**
 * @brief An action to set the collidability state of an entity.
 */
class SetCollidableAction : public Action
{
	public:
	/**
	 * @brief The default constructor.
	 * @param entity The entity those collidability is to be set.
	 * @param state The state to set the collidability.
	 */
	SetCollidableAction(Entity& entity, bool state);

    /**
     * @brief Activate this action.
     * @param level Level in which the action takes place.
     */
    virtual void activate(Level& level);

	private:
    // The entity whose interactable state is to be set.
    Entity& mEntity;

    // The state to set.
    bool mState;
};

#endif /* SETCOLLIDABLEACTION_HPP_ */
