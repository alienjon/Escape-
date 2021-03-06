/*
 * CollisionArea.hpp
 *
 *  Created on: Oct 20, 2011
 *      Author: alienjon
 */
#ifndef COLLISIONAREA_HPP_
#define COLLISIONAREA_HPP_

#include <list>

#include <SFML/Graphics.hpp>

/**
 * @brief This is a polygon specifically for collision areas.
 */
class CollisionArea
{
	public:
	virtual ~CollisionArea()
	{}

	/**
	 * @brief Add a shape to the area.
	 * @param rect The rectangle to add.
	 */
	virtual void add(const sf::FloatRect& rect);

	/**
	 * @brief Draw the collision area.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(sf::RenderWindow& renderer);

	/**
	 * @brief Check for intersections.
	 * @param area The area to check.
	 * @return True if an intersection exists.
	 */
	virtual bool isIntersecting(const sf::FloatRect& area) const;

	/**
	 * @brief Set the position of the area.
	 * @param x The x value.
	 * @param y The y value.
	 */
	virtual void setPosition(float x, float y);

	private:
	// The edges of the polygon.
	std::list<sf::FloatRect> mAreas;

	// The location of the area.
	sf::Vector2f mPosition;
};

#endif /* COLLISIONAREA_HPP_ */
