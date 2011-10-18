/*
 * Viewport
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */
#include "Viewport.hpp"

#include "../Entities/Entity.hpp"
#include "../main.hpp"
#include "../Managers/VideoManager.hpp"

Viewport::Viewport() :
	mDimension(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
	mEntity(0),
	mZoomX(1.0),
	mZoomY(1.0),
	mXOffset(0),
	mYOffset(0)
{
}

void Viewport::mCheckBounds()
{
    if(mDimension.vector.x < 0)
        mDimension.vector.x = 0;
    if(mDimension.vector.y < 0 )
        mDimension.vector.y = 0;
    if(mDimension.vector.x > (int)(mBounds.width - mDimension.width))
        mDimension.vector.x = mBounds.width - mDimension.width;
    if(mDimension.vector.y > (int)(mBounds.height - mDimension.height))
        mDimension.vector.y = mBounds.height - mDimension.height;
}

void Viewport::center(const Entity* entity)
{
	// Tie the object.
	mEntity = entity;
}

void Viewport::center(int x, int y)
{
    // Set the positions.
    mDimension.vector.x = x;
    mDimension.vector.y = y;

    // Check bounds.
    mCheckBounds();
}

int Viewport::getHeight() const
{
	return mDimension.height;
}

int Viewport::getWidth() const
{
	return mDimension.width;
}

int Viewport::getX() const
{
	return mDimension.vector.x;
}

int Viewport::getXOffset() const
{
	return mXOffset;
}

int Viewport::getY() const
{
	return mDimension.vector.y;
}

int Viewport::getYOffset() const
{
	return mYOffset;
}

bool Viewport::isOnScreen(const Rectangle& area) const
{
    return isOnScreen(area.vector.x, area.vector.y, area.width, area.height);
}

bool Viewport::isOnScreen(const SDL_Rect& area) const
{
    return isOnScreen(area.x, area.y, area.w, area.h);
}

bool Viewport::isOnScreen(const Quadrilateral& area) const
{
    return area.isIntersecting(mDimension);
}

bool Viewport::isOnScreen(int _x, int _y, int _w, int _h) const
{
    // Get the current area of the screen.
    int x = mDimension.vector.x;
    int y = mDimension.vector.y;
    int w = mDimension.width;
    int h = mDimension.height;
    return !((_x + _w) < x || _x >  (x + w) || (_y + _h) < y || _y > (y + h));
}

bool Viewport::isTracking() const
{
	return mEntity;
}

void Viewport::logic()
{
	// Center the camera on the current object.
	// @note All non-viewport aspects must be ratios via the zoom (in this case the entity)
	if(mEntity)
	{
	    center(((int(mEntity->getWidth() / 2) * mZoomX) - int(mDimension.width / 2) + (mEntity->getX() * mZoomX)),
	           ((int(mEntity->getHeight() / 2) * mZoomY) - int(mDimension.height / 2) + (mEntity->getY() * mZoomY)));
	}
}

void Viewport::setBounds(const Rectangle& bounds)
{
    mBounds = bounds;
}

void Viewport::setHeight(unsigned int height)
{
	mDimension.height = height;
}

void Viewport::setPosition(int x, int y)
{
    mDimension.vector.x = x;
    mDimension.vector.y = y;
    mCheckBounds();
}

void Viewport::setWidth(unsigned int width)
{
	mDimension.width = width;
}

void Viewport::setX(int x)
{
    mDimension.vector.x = x;
    mCheckBounds();
}

void Viewport::setXOffset(int xOffset)
{
	mXOffset = xOffset;
}

void Viewport::setY(int y)
{
    mDimension.vector.y = y;
    mCheckBounds();
}

void Viewport::setYOffset(int yOffset)
{
	mYOffset = yOffset;
}

void Viewport::setZoom(double zoomX, double zoomY)
{
	mZoomX = zoomX;
	mZoomY = zoomY;
}
