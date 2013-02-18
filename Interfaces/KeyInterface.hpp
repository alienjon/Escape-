/*
 * KeyInterface.hpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#ifndef KEYINTERFACE_HPP_
#define KEYINTERFACE_HPP_

#include <list>

#include <SFML/System.hpp>

#include "../Listeners/KeyListener.hpp"

/*
 * @brief Interface class for objects that will distribute keyboard input.
 */
class KeyInterface
{
	public:
	/**
	 * @brief Default constructor.
	 */
	KeyInterface();
	virtual ~KeyInterface();

	/**
	 * @brief Add a keyboard input listener.
	 * @param listener The listener to add.
	 */
	virtual void addKeyListener(KeyListener* listener);

	/**
	 * @brief Remove a keyboard input listener.
	 * @param listener The listener to remove.
	 */
	virtual void removeKeyListener(KeyListener* listener);

	protected:
	/**
	 * @brief Distribute an event to the listeners.
	 * @param event A key press event.
	 */
	virtual void distributeKeyPressed(const sf::Event& event);

	/**
	 * @brief Distribute an event to the listeners.
	 * @param event A key release event.
	 */
	virtual void distributeKeyReleased(const sf::Event& event);

	private:
	// The listeners for keyboard input.
	std::list<KeyListener*> mKeyListeners;
};

#endif /* KEYBOARDINPUTINTERFACE_HPP_ */
