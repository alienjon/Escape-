/*
 * GameInterfaceInterface.hpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */

#ifndef GAMEINTERFACEINTERFACE_HPP_
#define GAMEINTERFACEINTERFACE_HPP_

#include <list>
#include <string>

#include "../Listeners/InterfaceListener.hpp"
#include "../Math/Rectangle.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief An interface for interacting with various meta-game elements (such as the GUI).
 */
class GameInterfaceInterface
{
	public:
    /**
     * @brief Sets the current global interface listener.
     * @param listener The listener to set.
     */
    void setInterfaceListener(InterfaceListener* listener);

    /**
     * @brief Request a message display.
     * @param caption The caption.
     * @param message The message to display.
     * @param sprite The sprite keyword to use to display with the message.
     * @param keyword A keyword to pass when the conversation is closed.
     */
    static void mDisplayMessage(const std::string& caption, const std::string& message, const std::string& sprite, const std::string& keyword);

	/**
	 * @brief Focus the viewport.
	 * @param entity The entity onto which to set focus.
	 */
    static void mFocusViewport(const Entity* entity);

    /**
     * @brief Set the viewport focus at a point.
	 * @param x The x position.
	 * @param y The y position.
     */
    static void mFocusViewport(int x, int y);

    /**
     * @brief Set the viewport offset.
     * @return The viewport offset of the viewport.
     */
    static Vector mGetViewportOffset();

    /**
     * @brief Set the viewport bounds.
     * @param bounds The bounds to set.
     */
    static void mSetViewportBounds(const Rectangle& bounds);

	private:
    /**
     * A list of listeners to this level.
     */
    static InterfaceListener* mInterfaceListener;
};

#endif /* GAMEINTERFACEINTERFACE_HPP_ */
