/*
 * MiniMap.cpp
 *
 *  Created on: Oct 5, 2011
 *      Author: alienjon
 */
#include "MiniMap.hpp"

#include "../Entities/Entity.hpp"
#include "../Math/Rectangle.hpp"
#include "../Managers/VideoManager.hpp"

const double MINI_MAP_ZOOM = 0.15;

MiniMap::MiniMap() :
	mSurface(0)
{
	// Set the zoom factor.
	mViewport.setZoom(MINI_MAP_ZOOM, MINI_MAP_ZOOM);
}

void MiniMap::center(Entity* entity)
{
	mViewport.center(entity);
}

void MiniMap::draw(gcn::Graphics* graphics)
{
	if(mSurface)
	{
		graphics->pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));
		graphics->drawImage(mSurface, 0, 0);
		graphics->popClipArea();
	}
}

void MiniMap::logic()
{
	gcn::Container::logic();
	mViewport.logic();
}

void MiniMap::setHeight(int height)
{
	mViewport.setHeight(height);
	gcn::Container::setHeight(height);
}

void MiniMap::setMap(Surface* surface)
{
	// Set the original surface.
	mOrigSurface = surface;

	// Scale the surface.
	mSurface = VideoManager::zoom(mOrigSurface, MINI_MAP_ZOOM, MINI_MAP_ZOOM);

	// Set the bounds.
	mViewport.setBounds(Rectangle(0, 0, mSurface->getWidth(), mSurface->getHeight()));
}

void MiniMap::setSize(int width, int height)
{
	setHeight(height);
	setWidth(width);
}

void MiniMap::setWidth(int width)
{
	mViewport.setWidth(width);
	gcn::Container::setWidth(width);
}
