/*
 * FloatingTextListener.hpp
 *
 *  Created on: Nov 23, 2011
 *      Author: alienjon
 */
#ifndef FLOATINGTEXTLISTENER_HPP_
#define FLOATINGTEXTLISTENER_HPP_

#include <string>

#include <SFML/Graphics.hpp>

class FloatingTextListener
{
	public:
    /**
     * @brief Display a floating text on the screen for a short period of time.
     * @param str The text to display.
     * @param position The initial position to display the text (it will float up over a short period of time)
     * @param color The color of the text to display.
     */
    virtual void addFloatingText(const std::string& str, const sf::Vector2f& position, const sf::Color& color) = 0;
};

#endif /* FLOATINGTEXTLISTENER_HPP_ */
