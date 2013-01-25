/*
 * ZoomScreen.hpp
 *
 *  Created on: Nov 25, 2011
 *      Author: alienjon
 */
#ifndef ZOOMSCREEN_HPP_
#define ZOOMSCREEN_HPP_

#include "../Entities/Entity.hpp"
#include "../Engine/Timer.hpp"

class Level;

class ZoomScreen : public Entity
{
	public:
	/**
	 * @brief Default constructor.
	 * @param level The level to zoom.
	 */
	ZoomScreen(Level& level);

    /**
     * @brief This FlipScreen is colliding/interacting with an entity.
     * @param entity The entity this FlipScreen collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Perform logic.
     * @param level The level in which this entity exists.
     */
    virtual void logic(Level& level);

	private:
	// The level to zoom.
	Level& mLevel;

	// The zoom timer.
	Timer mTimer;

	// True if zooming in.
	bool mIsZooming;
};

#endif /* ZOOMSCREEN_HPP_ */
