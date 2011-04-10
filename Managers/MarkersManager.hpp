/*
 * MarkersManager.hpp
 *
 *  Created on: May 11, 2009
 *      Author: alienjon
 */

#ifndef MARKERS_HPP_
#define MARKERS_HPP_

#include <list>

#include <guichan.hpp>

#include "../Engine/Renderer.hpp"
#include "../Engine/Sprite.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief A class to allow the display of markers.
 */
class MarkersManager
{
    public:
    /**
     * @brief Manages and displays all markers.
     */
    MarkersManager();

    /**
     * @brief Add a marker to display.
     * @param p The point to show the marker.
     */
    virtual void addMarker(const Vector& p);

    /**
     * @brief Clear all markers.
     */
    virtual void clearMarkers();

    /**
     * @brief Draw the markers.
     * @param renderer The graphics object.
     */
    virtual void draw(Renderer& renderer);

    protected:
    /**
     * A marker's individual animation pause time.
     */
    static const unsigned int MARKER_ANIMATION_PAUSE;

    /**
     * A list of markers.
     */
    std::list<Vector> mMarkers;

    /**
     * The marker animation.
     */
    Sprite mMarker;
};

#endif /* MARKERS_HPP_ */
