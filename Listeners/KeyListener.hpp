/*
 * KeyListener.hpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#ifndef KEYLISTENER_HPP_
#define KEYLISTENER_HPP_

#include <SFML/Graphics.hpp>

class KeyListener
{
	public:
	virtual ~KeyListener() {}

	/**
	 * @brief A key was pressed.
	 * @param event The event details.
	 */
	virtual void keyPressed(const sf::Event& event) = 0;

	/**
	 * @brief A key was released.
	 * @param event The event details.
	 */
	virtual void keyReleased(const sf::Event& event) = 0;
};

#endif /* KEYLISTENER_HPP_ */
