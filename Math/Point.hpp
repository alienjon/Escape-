/*
 * Point.hpp
 *
 *  Created on: Sep 10, 2011
 *      Author: alienjon
 */

#ifndef POINT_HPP_
#define POINT_HPP_

#include <ostream>

/**
 * A point is an X,Y coordinate.  These are to be used for non-precise locations as
 * the X,Y value are integers.  For better accuracy (ie: rendering) @see Vector.
 * @note There are two constructors - a default that sets x,y to zero and another
 * where x and y are specified.  Default values are not provided to force the user
 * of this struct to either provide both values or neither (for error checking).
 */
struct Point
{
	/**
	 * Construct a null point.
	 */
	Point() : x(0), y(0)
	{}

	/**
	 * Construct a point where the values are provided.
	 * @param _x The x location.
	 * @param _y The y location.
	 */
	Point(int _x, int _y) : x(_x), y(_y)
	{}

	// The X,Y values.
	int x, y;
};

/**
 * @brief For displaying a point to the console.
 * @param os The output stream.
 * @param p The point to output.
 * @return The updated stream.
 */
std::ostream& operator<<(std::ostream& os, const Point& p);

#endif /* POINT_HPP_ */
