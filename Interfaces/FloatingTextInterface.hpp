/*
 * FloatingTextInterface.hpp
 *
 *  Created on: Nov 23, 2011
 *      Author: alienjon
 */
#ifndef FLOATINGTEXTINTERFACE_HPP_
#define FLOATINGTEXTINTERFACE_HPP_

#include <list>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Listeners/FloatingTextListener.hpp"

class FloatingTextInterface
{
	public:
	/**
	 * @brief Add a listener.
	 * @param listener The listener to add.
	 */
	void addFloatingTextListener(FloatingTextListener* listener)
	{
		mFloatingTextListeners.push_back(listener);
	}

	public:
    /**
     * @brief Display a floating text on the screen for a short period of time.
     * @param str The text to display.
     * @param position The initial position to display the text (it will float up over a short period of time)
     * @param color The color of the text to display.
     */
	void distributeFloatingText(const std::string& str, sf::Vector2f position, const sf::Color& color)
	{
		for(std::list<FloatingTextListener*>::iterator it = mFloatingTextListeners.begin(); it != mFloatingTextListeners.end(); ++it)
			(*it)->addFloatingText(str, position, color);
	}

	/**
	 * @brief Remove a listener.
	 * @param listener The listener to remove.
	 */
	void removeFloatingTextListener(FloatingTextListener* listener)
	{
		mFloatingTextListeners.remove(listener);
	}

	private:
	// The listeners.
	std::list<FloatingTextListener*> mFloatingTextListeners;
};

#endif /* FLOATINGTEXTINTERFACE_HPP_ */
