/*
 * Rectangle.hpp
 *
 *  Created on: Apr 30, 2009
 *      Author: alienjon
 */
#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include <ostream>

#include "SDL/SDL.h"

#include "../guichan.hpp"
#include "../Math/Polygon.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief A basic rectangle.
 *
 * The Rectangle not only defines a simple rectangle for the game, but additionally
 * provides an interface with SDL_Rect and gcn::Rectangle.  This object also allows
 * checking for intersections via each of these objects.
 */
struct Rectangle : public Polygon
{
    public:
    /**
     * @brief A rectangle that uses X and Y precisely.
     */
    Rectangle(double _x = 0, double _y = 0, unsigned int _w = 0, unsigned int _h = 0);

    /**
     * @brief For conversions.
     */
    Rectangle(const gcn::Rectangle& rect);

    /**
     * @brief For conversions.
     * @note This will discard the offsets.
     */
    Rectangle(const gcn::ClipRectangle& rect);

    /**
     * @brief For conversions.
     */
    Rectangle(const SDL_Rect& rect);

    /**
     * @brief For gcn::Rectangle conversions.
     */
    operator gcn::Rectangle();

    /**
     * @brief Get the center vector of the rectangle.
     * @return The center vector of the rectangle.
     */
    Vector getCenter() const;

	/**
	 * Determine the number of vectors in the polygon.
	 * @return The number of vectors.
	 */
	virtual const unsigned int getNumberOfPoints() const;

	/**
	 * Get the specified vector of the polygon.
	 * @param vector The vector to obtain.
	 * @return The vector at the requested position.
	 * @throws std::out_of_range thrown if 'vector' is out of range.
	 */
	virtual Vector getPoint(unsigned int vector) const;

    /**
     * @brief Check to see if this rectangle is intersecting with another rectangle.
     * @param area The area to check.
     * @return True if there is an intersection.
     */
    bool isIntersecting(const Rectangle& rectangle) const;

    /**
     * @brief Check to see if this dimension is intersecting with another rectangle.
     * @param area The area to check.
     * @return True if there is an intersection.
     */
    bool isIntersecting(double _x, double _y, int _w, int _h) const;

    /**
     * @brief Checks to see if the provided vector is in this rectangle.
     * @param _x The x position.
     * @param _y The y position.
     * @return True if the vector is within the rectangle.
     */
    bool isVectorInRect(const int _x, const int _y) const;

    /**
     * @brief Checks to see if the provided vector is in this rectangle.
     * @param vector The vector to check.
     * @return True if the vector is within the rectangle.
     */
    bool isVectorInRect(const Vector& p) const;

    /**
     * Precise X and Y coordinates.
     */
    Vector vector;

    /**
     * The dimension of the rectangle.
     */
    unsigned int width, height;
};

/**
 * @brief For displaying rectangles.
 * @param os The output stream.
 * @param rect The rectangle to display.
 * @return The updated output stream.
 */
std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

// A null rectangle.
extern const Rectangle NULL_RECTANGLE;

#endif /* RECTANGLE_HPP_ */
