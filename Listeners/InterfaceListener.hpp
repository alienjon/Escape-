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

class Creature;
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
     * @brief Add creature info to the GUI.
     * @param creature The creature whose info is to be displayed.
     */
    virtual void addCreatureDisplay(Creature* creature) = 0;

    /**
     * @brief Add a message to the messages section of the options menu.
     * @param title The message's title.
     * @param message The message itself.
     */
    virtual void addMessage(const std::string& title, const std::string& message) = 0;

    /**
     * @brief Add a task for the player to complete.
     * @param title The title for the task.
     * @param message A detailed message for the task.
     * @return The ID of the task.
     */
    virtual unsigned int addTask(const std::string& title, const std::string& message) = 0;

    /**
     * @brief Complete a task.
     * @param id The ID of the task that is now completed.
     */
    virtual void completeTask(unsigned int id) = 0;

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
     * @brief Remove a creature's health display from the GUI.
     * @param creature The creature whose display is to be removed.
     */
    virtual void removeCreatureDisplay(Creature* creature) = 0;

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

    /**
     * @brief Signal the letter indicator.
     */
    virtual void signalLetterIndicator() = 0;
};

#endif /* INTERFACELISTENER_HPP_ */
