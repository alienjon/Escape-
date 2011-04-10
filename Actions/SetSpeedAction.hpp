/*
 * SetSpeedAction.hpp
 *
 *  Created on: Apr 23, 2009
 *      Author: alienjon
 */

#ifndef SETSPEEDACTION_HPP_
#define SETSPEEDACTION_HPP_

#include "Action.hpp"

class Creature;

/**
 * @brief An action that sets the speed of a creature.
 */
class SetSpeedAction: public Action
{
	public:
	/**
	 * @brief Set the speed of the provided creature to the provided speed.
	 * @param creature The creature whose speed to set.
	 * @param speed The speed value (this is the number of ms it takes to move 1 step)
	 */
	SetSpeedAction(Creature& creature, double speed);
	virtual ~SetSpeedAction();

	/**
	 * @brief Activate the action.
	 * @param eData The environment data.
	 */
	virtual void activate(EnvironmentData& eData);

	protected:
	/**
	 * The creature.
	 */
	Creature* mCreature;

	/**
	 * The speed.
	 */
	double mSpeed;
};

#endif /* SETSPEEDACTION_HPP_ */
