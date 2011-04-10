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
#include "Surface.hpp"

const unsigned int ANIMATION_IMAGE_PAUSE = 50;

Surface::Surface(SDL_Surface* image, const Rectangle& area) : gcn::SDLImage(image, false),
															  mPause(ANIMATION_IMAGE_PAUSE),
															  mArea(area)
{
}

inline int Surface::getHeight() const
{
	return (mArea.height > 0) ? mArea.height : gcn::SDLImage::getHeight();
}

inline unsigned int Surface::getPause() const
{
	return mPause;
}

inline int Surface::getWidth() const
{
	return (mArea.width > 0) ? mArea.width : gcn::SDLImage::getWidth();
}

inline void Surface::setPause(unsigned int pause)
{
	mPause = pause;
}
