/*
 * MiniMap.hpp
 *
 *  Created on: Oct 5, 2011
 *      Author: alienjon
 */
#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include "../guichan.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Surface.hpp"
#include "../Engine/Viewport.hpp"

class Entity;

/**
 * @brief The mini-map displays a small version of the map with a black mask that
 * covers the areas of the map the player has not yet been.
 */
class MiniMap: public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 */
	MiniMap();

	/**
	 * @brief Center the mini map on an entity.
	 * @param entity The entity to center upon.
	 */
	virtual void center(Entity* entity);

	/**
	 * @brief Draw the widget.
	 * @param graphics The graphics object.
	 */
	virtual void draw(gcn::Graphics* graphics);

	/**
	 * @brief Perform logic.
	 */
	virtual void logic();

	/**
	 * @brief Set the height.
	 * @param height The new height.
	 */
	virtual void setHeight(int height);

	/**
	 * @brief Set the mini-map.
	 * @param surface The full map
	 */
	virtual void setMap(Surface* surface);

	/**
	 * @brief Set the size.
	 * @param width The width.
	 * @param height The height.
	 */
	virtual void setSize(int width, int height);

	/**
	 * @brief Set the width.
	 * @param width The width.
	 */
	virtual void setWidth(int width);

	private:
	// This is the original image.
	Surface* mOrigSurface;

	// This is the current (zoomed) surface.
	Surface* mSurface;

	// The viewport for the mini map.
	Viewport mViewport;
};

#endif /* MINIMAP_HPP_ */
