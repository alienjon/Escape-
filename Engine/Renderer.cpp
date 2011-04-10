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
#include "Renderer.hpp"

#include <stdexcept>

#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "../Game/Game.hpp"
#include "Logger.hpp"
#include "../main.hpp"
#include "Surface.hpp"
#include "../Managers/VideoManager.hpp"

using std::runtime_error;
using std::string;

Renderer::Renderer() :
	mIsFullscreen(false),
	mLowerTarget(0),
	mUpperTarget(0)
{
	// Linux-specific code.
#ifdef __linux__
	putenv("SDL_VIDEODRIVER=x11");
	Logger::log("Setting video driver to x11");
	/*
	 * Available options
	 * Linux: x11 (default), dga, fbcon, directfb, svgalib, ggi, aalib
	 * Windows: directx (default), windib
	 */
#endif

    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        throw runtime_error(string("SDL video initialization failed: ") + SDL_GetError());
    }
    else
    {
        Logger::log("Video initialization successful.");
    }

    // Disable the key repeat.
    SDL_EnableKeyRepeat(0, 0);

    // Enable unicode.
    SDL_EnableUNICODE(true);

    // Don't show the regular cursor.
    SDL_ShowCursor(false);

    // Set Caption
    SDL_WM_SetCaption(GAME_NAME.c_str(), string(GAME_NAME + " v." + GAME_VERSION).c_str());

    // Set Icon
    SDL_Surface* icon = IMG_Load(FILE_GAME_ICON);

    if(icon)
    {
        SDL_WM_SetIcon(icon, 0);
    }
    else
    {
        Logger::log("Icon '" + string(FILE_GAME_ICON) + "' not found, no icon loaded.");
    }

    SDL_FreeSurface(icon);

    // Initially initialize the video for full options.
    initialize();
}

Renderer::~Renderer()
{
	// Delete the screen surface.
	SDL_FreeSurface(mLowerTarget);
	SDL_FreeSurface(mUpperTarget);

	// Show the cursor on exiting.
	SDL_ShowCursor(true);

	// Quit SDL.
	SDL_Quit();
}

void Renderer::applyLayers()
{
	// Make sure that the lower layer is the target.
	setRenderingLayer(0);

	// Blit the upper layers (in order) above the lower layer.
	SDL_BlitSurface(mUpperTarget, 0, mLowerTarget, 0);
}

void Renderer::clearScreen()
{
	const gcn::Color& c = getColor();
	boxRGBA(mTarget, 0, 0, mTarget->w, mTarget->h, c.r, c.g, c.b, c.a);
}

void Renderer::drawImage(const Surface* image, int x, int y)
{
	drawImage(image, image->mArea.vector.x, image->mArea.vector.y, x, y, image->getWidth(), image->getHeight());
}

void Renderer::drawImage(const Surface* image, int srcX, int srcY, int dstX, int dstY, int width, int height)
{
	if(mClipStack.empty())
	{
		throw runtime_error("Renderer::drawImage() -> Clip stack is empty.  Was draw() called outside of _beginDraw() and _endDraw()?");
	}

	const gcn::ClipRectangle& top = mClipStack.top();
	SDL_Rect src;
	SDL_Rect dst;
	src.x = srcX;
	src.y = srcY;
	src.w = width;
	src.h = height;
	dst.x = dstX + top.xOffset;
	dst.y = dstY + top.yOffset;

	SDL_BlitSurface(image->mSurface, &src, mTarget, &dst);
}

void Renderer::fillEllipse(const Ellipse& ellipse)
{
	// Get the color and draw the ellipse.
	const gcn::Color& c = getColor();
	filledEllipseRGBA(mTarget, ellipse.center.x, ellipse.center.y, ellipse.xRad, ellipse.yRad, c.r, c.g, c.b, c.a);
}

void Renderer::fillQuadrilateral(const Quadrilateral& quad)
{
    // The lists of X and Y points.
    Sint16 xList[] = {quad.p1.x, quad.p2.x, quad.p3.x, quad.p4.x};
    Sint16 yList[] = {quad.p1.y, quad.p2.y, quad.p3.y, quad.p4.y};

    // Draw onto the screen (if it is, in fact, on the screen)
    // Note: The 4 ('n', in the documentation) is the number of sides of the polygon.
    const gcn::Color& c = getColor();
    filledPolygonRGBA(mTarget, xList, yList, 4, c.r, c.g, c.b, c.a);
}

unsigned int Renderer::getFontHeight() const
{
	if(mFont)
	{
		return mFont->getHeight();
	}

	throw runtime_error("Renderer::getFontHeight() -> Null font currently set.");
}

unsigned int Renderer::getFontWidth(const string& message) const
{
	if(mFont)
	{
		return mFont->getWidth(message);
	}

	throw runtime_error("Renderer::getFontWidth() -> Null font currently set.");
}

void Renderer::initialize(bool fs)
{
    // Set the SDL video flags.
    int flags = SDL_ANYFORMAT | SDL_SWSURFACE;
    if(fs)
    {
        flags |= SDL_FULLSCREEN;
    }

    // Store the full screen value.
    mIsFullscreen = fs;

    // SDL handles the screen surface memory management
    mTarget = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, flags);
    if(!(mLowerTarget = mTarget))
    {
        throw runtime_error(string("video.cpp::initVideo()-> Cannot create screen surface: ") + SDL_GetError());
    }

    // Now create a surface for the upper level.
    mUpperTarget = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_SetColorKey(mUpperTarget, SDL_SRCCOLORKEY, SDL_MapRGB(mUpperTarget->format, 255, 0, 255));
}

void Renderer::render()
{
	// Flip the screen surface.
	SDL_Flip(mTarget);
}

void Renderer::setRenderingLayer(unsigned int layer)
{
	if(layer == 0)
	{
		mTarget = mLowerTarget;
	}
	else if(layer == 1)
	{
		mTarget = mUpperTarget;
	}
	else
	{
		throw runtime_error("Renderer::setRenderingLayer() -> Invalid rendering layer.");
	}
}

void Renderer::takeScreenshot()
{
	// Each time a shot is taken, increment the screenshot number.
	static int shotNumber = 0;

	// Determine the filename.
	string filename = string("SCREENSHOT_" + toString(shotNumber++)) + ".bmp";

	// Save the file.
	if(SDL_SaveBMP(mTarget, filename.c_str()))
	{
		Logger::log("Error saving '" + filename + "'.");
	}
}

void Renderer::toggleFullscreen()
{
    // Toggle the fullscreen variable.
    initialize(!mIsFullscreen);
}
