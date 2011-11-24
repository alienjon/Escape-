/*
 * Key.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef KEY_HPP_
#define KEY_HPP_

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Interfaces/RemoveLockInterface.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief A key entity is an item to be picked up by the player to unlock something/end the level.
 */
class KeyEntity : public Entity
{
	public:
	/**
	 * @brief Default constructor.
	 * @param color The color of this key.
	 */
	KeyEntity(sf::Color color);

    /**
     * @brief This KeyEntity is colliding/interacting with an entity.
     * @param entity The entity this KeyEntity collided into.
     */
    virtual void collide(Entity& entity);

	/**
	 * @brief Perform logic.
	 * @param level The level in which this entity resides.
	 */
	virtual void logic(Level& level);

	private:
	// The key's color.
	sf::Color mColor;

	// If not growing, then it is shrinking.
	bool mIsGrowing;

	// The drawing area of the entity.
	sf::Vector2f mSize;

	// The animation timer.
	Timer mTimer;
};

#endif /* KEY_HPP_ */
