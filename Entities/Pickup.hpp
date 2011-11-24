/*
 * Pickup.hpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#ifndef PICKUP_HPP_
#define PICKUP_HPP_

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"

/**
 * @brief A pickup is something that the player picks up to get points.
 */
class Pickup : public Entity
{
	public:
	/**
	 * @brief Default constructor.
	 * @param value The value of the pickup.
	 * @param color The color of the pickup.
	 * @param size The size of the pickup.
	 */
	Pickup(int value, const sf::Color& color, unsigned int size);

    /**
     * @brief This KeyEntity is colliding/interacting with an entity.
     * @param entity The entity this KeyEntity collided into.
     */
    virtual void collide(Entity& entity);

	private:
	// The value of the pickup.
	int mValue;

	// The size of the pickup.
	unsigned int mSize;

	// The color of the pickup.
	sf::Color mColor;
};

#endif /* PICKUP_HPP_ */
