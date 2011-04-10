/*
 * MarkersManager.cpp
 *
 *  Created on: May 11, 2009
 *      Author: alienjon
 */

#include "MarkersManager.hpp"

#include "AnimationManager.hpp"

using std::list;

MarkersManager::MarkersManager()// @todo need to fix up animations : mMarker(AnimationManager::getGameAnimation(GAMEANIMATIONTYPE_MARKER))
{
}

void MarkersManager::addMarker(const Vector& p)
{
    mMarkers.push_back(p);
}

void MarkersManager::clearMarkers()
{
    mMarkers.clear();
}

void MarkersManager::draw(Renderer& renderer)
{
    // Draw the markers on the screen.
    for(list<Vector>::iterator it = mMarkers.begin(); it != mMarkers.end(); ++it)
    {
    	mMarker.draw(renderer, it->x - (mMarker.getWidth() / 2), it->y - (mMarker.getHeight()));
    }
}

const unsigned int MarkersManager::MARKER_ANIMATION_PAUSE = 150;
