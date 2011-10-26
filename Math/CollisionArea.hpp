/*
 * CollisionArea.hpp
 *
 *  Created on: Oct 20, 2011
 *      Author: alienjon
 */
#ifndef COLLISIONAREA_HPP_
#define COLLISIONAREA_HPP_

#include <list>

#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"

/**
 * @brief This is a polygon specifically for collision areas.
 */
class CollisionArea
{
	public:
	/**
	 * @brief Add a rectangle to the area.
	 * @param rect The rectangle to add.
	 */
	virtual void addRectangle(const Rectangle& rect);

	/**
	 * @brief Add a integer to the X values in all rectangles.
	 * @param x The x value to add.
	 */
	virtual void addX(int x);

	/**
	 * @brief Add a integer to the Y values in all rectangles.
	 * @param y The y value to add.
	 */
	virtual void addY(int y);

	/**
	 * @brief Draw the collision area.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(Renderer& renderer);

	/**
	 * @brief Check for intersections.
	 * @param rect The rectangle with which to check.
	 * @return True if an intersection exists.
	 */
	virtual bool isIntersecting(const Rectangle& rect) const;

	private:
	// The edges of the polygon.
	std::list<Rectangle> mAreas;
};

#endif /* COLLISIONAREA_HPP_ */
