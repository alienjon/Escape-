/*
 * FlipScreen.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: alienjon
 */
#ifndef FLIPSCREEN_HPP_
#define FLIPSCREEN_HPP_

#include "../Entities/ImageEntity.hpp"
#include "../Engine/Timer.hpp"

class Level;

class FlipScreen : public ImageEntity
{
	public:
	/**
	 * @brief Construct a screen.
	 * @param level The level to flip.
	 */
	FlipScreen(Level& level);

    /**
     * @brief This FlipScreen is colliding/interacting with an entity.
     * @param entity The entity this FlipScreen collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Perform logic.
     * @param level The level in which the screen exists.
     */
    virtual void logic(Level& level);

	private:
	// The level to flip.
	Level& mLevel;

	// Rotate timer.
	Timer mTimer;
};

#endif /* FLIPSCREEN_HPP_ */
