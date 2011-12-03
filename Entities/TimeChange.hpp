/*
 * TimeChange.hpp
 *
 *  Created on: Nov 29, 2011
 *      Author: alienjon
 */
#ifndef TIMECHANGE_HPP_
#define TIMECHANGE_HPP_

#include "../Entities/ImageEntity.hpp"
#include "../Engine/Timer.hpp"

class Level;

class TimeChange : public ImageEntity
{
	public:
	/**
	 * @brief Default constructor.
	 * @param level The level in which the time change is taking place.
	 */
	TimeChange(Level& level);

	/**
	 * @brief A collision took place.
	 * @param entity The entity that collided with this entity.
	 */
	virtual void collide(Entity& entity);

	/**
	 * @brief Perform logic.
	 * @param level The level in which this entity exists.
	 */
	virtual void logic(Level& level);

	private:
	// The level.
	Level& mLevel;

	// Adding time if true, subtracting if false.
	bool mIsAdding;

	// The timer to determine when to change from + to -.
	Timer mTimer;

	// The interval to wait until the change next occurs.
	unsigned int mInterval;
};

#endif /* TIMECHANGE_HPP_ */
