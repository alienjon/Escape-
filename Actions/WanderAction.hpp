/*
 * WanderAction.hpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */

#ifndef WanderAction_HPP_
#define WanderAction_HPP_

#include "Action.hpp"

class Creature;

/**
 * @brief An action that tells a creature to wander.
 */
class WanderAction: public Action
{
	public:
	/**
	 * @brief Tell the specifed creature to wander.
	 * @param creature The creature to have wander.
	 */
	WanderAction(Creature* creature);
	virtual ~WanderAction();

	/**
	 * @brief Activate the action and have the creature wander.
	 * @param eData The environment data.
	 */
	virtual void activate(EnvironmentData& eData);

	protected:
	/**
	 * The creature.
	 */
	Creature* mCreature;
};

#endif /* WanderAction_HPP_ */
