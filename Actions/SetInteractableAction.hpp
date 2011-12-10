/*
 * SetInteractableAction.hpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#ifndef SETINTERACTABLEACTION_HPP_
#define SETINTERACTABLEACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Entities/Entity.hpp"

/**
 * @brief An action to set the interactability state of an entity.
 */
class SetInteractableAction : public Action
{
	public:
	/**
	 * @brief The default constructor.
	 * @param entity The entity whose interactability state is to be set.
	 * @param state The state of the interactability to set.
	 */
	SetInteractableAction(Entity& entity, bool state);

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

#endif /* SETINTERACTABLEACTION_HPP_ */
