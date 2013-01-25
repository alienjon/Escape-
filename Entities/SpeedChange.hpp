/*
 * SpeedChange.hpp
 *
 *  Created on: Nov 30, 2011
 *      Author: alienjon
 */
#ifndef SPEEDCHANGE_HPP_
#define SPEEDCHANGE_HPP_

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Engine/Timer.hpp"

class Creature;
class Level;

class SpeedChange : public Entity
{
	public:
	/**
	 * @brief Construct a speed change entity.
	 * @param speed The speed to change the entity when activated.
	 * @param creature The creature whose speed is to be changed.
	 */
	SpeedChange(float speed, Creature& creature);

	/**
	 * @brief The entity collided with another entity.
	 * @param entity The entity collided with.
	 */
	virtual void collide(Entity& entity);

	/**
	 * @brief Draw the entity.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(sf::RenderWindow& renderer);

	/**
	 * @brief Perform logic.
	 * @param level The current level.
	 */
	virtual void logic(Level& level);

	private:
	// The speed to set for the player.
	float mSpeed;

	// The level in which this entity resides.
	Creature& mCreature;

    // Player speed change data.
    Timer mTimer;
};

#endif /* SPEEDCHANGE_HPP_ */
