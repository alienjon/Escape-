/***************************************************************************
 *   Copyright (C) 2007 by Jonathan Rosen   *
 *   holy.smoking.floorboards.batman@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SURFACE_H
#define SURFACE_H

#include "SDL/SDL.h"

#include "../Guichan/sdl.hpp"

#include "../Math/Rectangle.hpp"

/**
 * @brief This game's implementation of a gcn::SDLImage.
 */
class Surface : public gcn::SDLImage
{
	// The renderer needs the surface for drawing.
	friend class Renderer;

	public:
	/**
	 * @brief Creates a new Surface.
	 * @param image The surface image.
	 * @param area The area of the SDL_Surface* to draw.
	 */
	Surface(SDL_Surface* image, const Rectangle& area = NULL_RECTANGLE);

	/**
	 * @brief Get the height.
	 * @return The height.
	 */
	virtual int getHeight() const;

	/**
	 * @brief Get the amount of time this Surface has to wait (in ms) before the next image in an animation is shown.
	 * @return The pause interval for the surface before the next image in the animation is shown.
	 */
	virtual unsigned int getPause() const;

	/**
	 * @brief Get the width.
	 * @return The width.
	 */
	virtual int getWidth() const;

	/**
	 * @brief Set the pause interval.
	 * @param pause The pause interval to set.
	 */
	virtual void setPause(unsigned int pause);

	private:
	/**
	 * The time this surface spends being displayed on the screen at showing.
	 */
	unsigned int mPause; // @todo move pause to sprite

	/**
	 * The area of the surface to draw.
	 */
	Rectangle mArea;
};

#endif
