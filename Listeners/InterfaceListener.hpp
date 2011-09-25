/*
 * InterfaceListener.hpp
 *
 *  Created on: Jun 3, 2010
 *      Author: the-saint
 */

#ifndef INTERFACELISTENER_HPP_
#define INTERFACELISTENER_HPP_

#include <string>

#include "../Math/Rectangle.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief An interface listener is an object with access to display elements of the game.
 * As such, these methods affect the GUI and other 'meta-game' elements (such as the
 * journalling/note system).
 */
class InterfaceListener
{
	public:
    /**
     * @brief Messages can be things like tutorials or even conversations.
     * @param caption The caption.
     * @param message The message to display.
     * @param sprite The sprite keyword to use to display with the message.
     * @param keyword A keyword to pass when the conversation is closed.
     * @note The image can be an empty string and a default image will display.
     */
    virtual void displayMessage(const std::string& caption, const std::string& message, const std::string& sprite, const std::string& keyword) = 0;

    /**
     * @brief Get the viewport's offset.
     * @return The offset.
     */
    virtual Vector getViewportOffset() const = 0;

	/**
	 * @brief Set the viewport's bounds.
	 * @param bounds The bounds to set.
	 */
	virtual void setViewportBounds(const Rectangle& bounds) = 0;

	/**
	 * @brief Set the viewport's focus.
	 * @param entity The entity onto which to set focus.
	 */
	virtual void setViewportFocus(const Entity* entity) = 0;

	/**
	 * @brief Set the viewport's focus.
	 * @param x The x position.
	 * @param y The y position.
	 */
	virtual void setViewportFocus(int x, int y) = 0;
};

#endif /* INTERFACELISTENER_HPP_ */
