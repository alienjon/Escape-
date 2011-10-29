/*
 * Key.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef KEY_HPP_
#define KEY_HPP_

#include "../Entities/Entity.hpp"
#include "../guichan.hpp"
#include "../Interfaces/RemoveLockInterface.hpp"

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
	KeyEntity(gcn::Color color);

    /**
     * @brief This KeyEntity is colliding/interacting with an entity.
     * @param entity The entity this KeyEntity collided into.
     */
    virtual void collide(Entity& entity);

	/**
	 * @brief Draw the key.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(Renderer& renderer);

	private:
	// The key's color.
	gcn::Color mColor;
};

#endif /* KEY_HPP_ */
