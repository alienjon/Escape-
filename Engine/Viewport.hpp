/*
 * Viewport
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */

#ifndef VIEWPORT_HPP_
#define VIEWPORT_HPP_

#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief Manages the area to be displayed on the screen.
 *
 * In addition to determining what is currently being shown on the screen,
 * the viewport can be focused on individual being's (usually the player) and
 * will track that being's movement.
 */
class Viewport
{
	public:
    /**
     * @brief The viewport shows the user what's on the screen.
     */
	Viewport();

	/**
	 * @brief Center the viewport on the specified being.
	 * @param being The being to center on.
	 * @note Pass 0 (zero) to focus on the currently selected being.
	 */
	virtual void center(const Entity* being = 0);

	/**
	 * @brief Center the viewport on a specified location.
	 * @param x The x location to focus on.
	 * @param y The y location to focus on.
	 */
	virtual void center(int x, int y);

    /**
     * @brief Get the height of the viewport's area.
     * @return The viewport's height.
     */
    virtual int getHeight() const;

    /**
     * @brief Get the offset.
     * @return The offset.
     */
    virtual Vector getOffset() const;

    /**
     * @brief Get the width of the viewport's area.
     * @return The viewport's width.
     */
    virtual int getWidth() const;

	/**
	 * @brief Get the viewport's current X coordinate.
	 * @return The current X coordinate.
	 */
	virtual int getX() const;

	/**
	 * @brief Get the viewport's current Y coordinate.
	 * @return The current Y coordinate.
	 */
	virtual int getY() const;

	/**
	 * @brief Checks of an area is on screen.
	 * @param area The area to check.
	 * @return True if the area is on screen (in the view of the viewport)
	 */
	virtual bool isOnScreen(const Rectangle& area) const;

    /**
     * @brief Checks of an area is on screen.
     * @param area The area to check.
     * @return True if the area is on screen (in the view of the viewport)
     */
    virtual bool isOnScreen(const SDL_Rect& area) const;

    /**
     * @brief Checks of an area is on screen.
     * @param area The area to check.
     * @return True if the area is on screen (in the view of the viewport)
     */
    virtual bool isOnScreen(const Quadrilateral& area) const;

    /**
     * @brief Checks if an area is on screen.
     * @param x The x position of the area.
     * @param y The y position of the area.
     * @param w The width of the area.
     * @param h The height of the area.
     */
    virtual bool isOnScreen(int x, int y, int w, int h) const;

    /**
     * @brief Returns true if the viewport is tracking the movement of an entity.
     * @return True if the viewport is tracking an entity.
     */
    virtual bool isTracking() const;

	/**
	 * @brief Perform viewport logic.
	 */
	virtual void logic();

	/**
	 * @brief The bounds this viewport will work within.
	 * @param bounds The bounds.
	 */
	virtual void setBounds(const Rectangle& bounds);

	/**
	 * @brief Set the viewport's position.
	 * @param x The new x position.
	 * @param y The new y position.
	 */
	virtual void setPosition(int x, int y);

	/**
	 * @brief Set the X position.
	 * @param x The new X position.
	 */
	virtual void setX(int x);

	/**
	 * @brief Set the Y position.
	 * @param y The new Y position.
	 */
	virtual void setY(int y);

	protected:
	/*
	 * The dimension of the viewport.
	 */
	Rectangle mDimension;

	/**
	 * The bounds the viewport will look within.
	 */
	Rectangle mBounds;

	/**
	 * @brief The currently focused-upon being.
	 */
	const Entity* mEntity;

	private:
	/**
	 * @brief Check that the position is within bounds.
	 */
	void mCheckBounds();
};

#endif /* VIEWPORT_HPP_ */
