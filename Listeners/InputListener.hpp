/*
 * InputListener.hpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#ifndef INPUTLISTENER_HPP_
#define INPUTLISTENER_HPP_

#include <SFML/System.hpp>

class InputListener
{
	public:
	virtual ~InputListener() {}

	/**
	 * @brief Handle input.
	 * @param event The input event.
	 * @return true if the event was consumed (used).
	 */
	virtual bool handleInput(const sf::Event& event) = 0;
};

#endif /* INPUTLISTENER_HPP_ */
