/*
 * Item.hpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

#include "../Entities/Entity.hpp"

/*
 * @brief An object the player can pick up and use.
 */
class Item : public Entity
{
	public:
	virtual ~Item()
	{}

	/**
	 * @brief The item has collided with an entity.
	 * @param entity The entity collided with.
	 */
	virtual void collide(Entity& entity);

	/**
	 * @brief Draw the item.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(sf::RenderWindow& renderer);

	/**
	 * @brief Get the filename of the item's image.
	 * @return The filename of the item's image.
	 */
	virtual const std::string& getImageFilename() const = 0;

	/**
	 * @brief Use the item.
	 */
	void use();

	protected:
	/**
	 * @brief Default constructor.
	 */
	Item();

	/**
	 * @brief Perform the item's specific action.
	 * @note This is to be overwritten but child classes so that the actual effects occur when 'use()' is called.
	 */
	virtual void mPerform()
	{}

	private:
	// True if the item is being drawn on the map.
	bool mIsDrawing;
};

#endif /* ITEM_HPP_ */
