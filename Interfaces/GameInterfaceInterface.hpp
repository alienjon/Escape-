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

class Creature;
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

	protected:
    /**
     * @brief Add a creature display.
     * @param creature The creature whose info is to be displayed.
     */
    static void mAddCreatureDisplay(Creature* creature);

    /**
     * @brief Add a message for the user to read.
     * @param title The message's title.
     * @param message The message itself.
     */
    static void mAddMessage(const std::string& title, const std::string& message);

    /**
     * @brief Add a task.
     * @param title The title of the task to add.
     * @param message The detailed message of the task to add.
     * @return The ID of the new task.
     */
    static unsigned int mAddTask(const std::string& title, const std::string& message);

    /**
     * @brief Complete a task.
     * @param id The ID of the task to complete.
     */
    static void mCompleteTask(unsigned int id);

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
     * @brief Remove a creature display
     * @param creature The creature whose display is to be removed.
     */
    static void mRemoveCreatureDisplay(Creature* creature);

    /**
     * @brief Set the viewport bounds.
     * @param bounds The bounds to set.
     */
    static void mSetViewportBounds(const Rectangle& bounds);

    /**
     * @brief Indicate that a letter was received.
     */
    static void mSignalLetter();

	private:
    /**
     * A list of listeners to this level.
     */
    static InterfaceListener* mInterfaceListener;
};

#endif /* GAMEINTERFACEINTERFACE_HPP_ */
