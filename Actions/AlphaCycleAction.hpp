/*
 * AlphaCycleAction.hpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#ifndef ALPHACYCLEACTION_HPP_
#define ALPHACYCLEACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Listeners/CreatureWaypointListener.hpp"
#include "../Engine/Timer.hpp"

class Entity;
class Level;

/**
 * @brief An action to decrease and then increase the alpha level of a drawable.
 */
class AlphaCycleAction : public Action, public CreatureWaypointListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param entity The cycling entity.
	 */
	AlphaCycleAction(Entity& entity);
	virtual ~AlphaCycleAction();

	/**
	 * @brief Activate the action (action logic).
	 * @param level The level in which the action is activating.
	 */
	virtual void activate(Level& level);

	/**
	 * @brief The creature has moved to a waypoint.
	 * @param creature The creature that moved.
	 */
	virtual void creatureMoved(Creature& creature);

	private:
	// The entity.
	Entity& mEntity;

	// The animation timer.
	Timer mTimer;

	// If true, the alpha level is increasing.
	bool mIncreaseAlpha;

	// The original alpha value.
	unsigned int mOriginalAlpha;
};

#endif /* ALPHACYCLEACTION_HPP_ */
