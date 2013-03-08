/*
 * TimeChange.hpp
 *
 *  Created on: Nov 29, 2011
 *      Author: alienjon
 */
#ifndef TIMECHANGE_HPP_
#define TIMECHANGE_HPP_

#include "../Entities/Entity.hpp"
#include "../Engine/Timer.hpp"
#include "../Interfaces/TimeChangeInterface.hpp"

class TimeChange : public Entity, public TimeChangeInterface
{
	public:
	/**
	 * @brief Default constructor.
	 */
	TimeChange();

	/**
	 * @brief A collision took place.
	 * @param entity The entity that collided with this entity.
	 */
	virtual void collide(Entity& entity);

	/**
	 * @brief Perform logic.
	 * @param level The level in which this entity exists.
	 * @param delta The time since the last frame displayed.
	 */
	virtual void logic(Level& level, int delta);

	private:
	// Adding time if true, subtracting if false.
	bool mIsAdding;

	// The timer to determine when to change from + to -.
	Timer mTimer;

	// The interval to wait until the change next occurs.
	unsigned int mInterval;
};

#endif /* TIMECHANGE_HPP_ */
