/*
 * FlipScreen.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: alienjon
 */
#ifndef FLIPSCREEN_HPP_
#define FLIPSCREEN_HPP_

#include "../Entities/Entity.hpp"

class Level;

class FlipScreen : public Entity
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

	private:
	// The level to flip.
	Level& mLevel;
};

#endif /* FLIPSCREEN_HPP_ */
