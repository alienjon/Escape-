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
#ifndef RENDERER_H
#define RENDERER_H

#include <list>
#include <string>

#include "SDL/SDL.h" // @note Needs to be placed before guichan/sdl.hpp

#include "../Math/Quadrilateral.hpp"
#include "../Guichan/sdl.hpp"

class Surface;

/**
 * @brief A reimplementation of gcn::SDLGraphics that provides extended functionality.
 *
 * The Renderer class allows for initialization of the video screen as well as extra
 * drawing functions (via SDL_gfx)
 */
class Renderer : public gcn::SDLGraphics
{
	public:
    /**
     * @brief The renderer object initializes SDL as well as handles all drawing, etc...
     */
    Renderer();
    virtual ~Renderer();

    /**
     * @brief Applies all layers onto each other in order.
     */
    virtual void applyLayers();

    /**
     * @brief Clear the screen with the currently assigned color.
     */
    virtual void clearScreen();

    /**
     * @brief Draw a surface.
     * @param surface The surface to draw.
     * @param x The x position to draw.
     * @param y The y position to draw.
     */
    virtual void drawImage(const Surface* image, int x, int y);

    /**
     * @brief Draw a surface.
     * @param surface The surface to draw.
     * @param srcX The source x coordinate.
     * @param srcY The source y coordinate.
     * @param dstX The destination x coordinate.
     * @param dstY The destination y coordinate.
     * @param width The width.
     * @param height The height.
     */
    virtual void drawImage(const Surface* image, int srcX, int srcY, int dstX, int dstY, int width, int height);

    /**
     * @brief Draw a filled ellipse.
     * @param x The x position of the ellipse.
     * @param y The y position of the ellipse.
     * @param width The width of the ellipse.
     * @param height The height of the ellipse.
     */
    virtual void fillEllipse(int x, int y, unsigned int width, unsigned int height);

	/**
	 * @brief Draw a filled quadrilateral onto the current layer.
	 * @param quad The quadrilateral to draw.
	 */
	virtual void fillQuadrilateral(const Quadrilateral& quad);

	/**
	 * @brief Returns the loaded font height.
	 * @return The font height.
	 */
	virtual unsigned int getFontHeight() const;

	/**
	 * @brief Returns the loaded font width.
	 * @param message The message of which to get the width.
	 * @return The font width.
	 */
	virtual unsigned int getFontWidth(const std::string& message) const;

    /**
     * @brief Initialize the video screen surface and inform user of any errors.
     * @param fs Reinitialize to full screen.
     */
    virtual void initialize(bool fs = false);

    /**
     * @brief Set the rendering surface layer.
     * @param layer 0 for lower layer, 1 for upper layer.
     *
     * @note As most rendering is done in the lower layer, the method that calls this should also reset the layer to lower (0) before returning.
     */
    virtual void setRenderingLayer(unsigned int layer);

	/**
	 * @brief Takes a screenshot.
	 */
	virtual void takeScreenshot();

    /**
     * @brief Toggle fullscreen
     */
    virtual void toggleFullscreen();

	/**
	 * @brief Draw the current buffer to the physical screen.
	 */
	virtual void render();

	protected:
	/**
	 * The full screen state.
	 */
	bool mIsFullscreen;

	/**
	 * This is a surface for the upper and lower layers.
	 */
	SDL_Surface* mLowerTarget; // This is mTarget.
	SDL_Surface* mUpperTarget;
};

#endif
