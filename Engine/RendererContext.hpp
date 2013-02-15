/*
 * RendererContext.hpp
 *
 *  Created on: Feb 14, 2013
 *      Author: alienjon
 */
#ifndef RENDERERCONTEXT_HPP_
#define RENDERERCONTEXT_HPP_

#include <SFML/Graphics.hpp>

/*
 * @brief Information needed to create the render window.
 */
struct RendererContext
{
	public:
	/**
	 * @brief The default constructor.
	 */
	RendererContext();

	// The screen details.
	sf::VideoMode mVideoMode;

	bool mFullscreen,	// Fullscreen toggle.
		 mVerticalSync;	// The vertical sync.

	// The context settings.
	sf::ContextSettings mContextSettings;
};

#endif /* RENDERERCONTEXT_HPP_ */
