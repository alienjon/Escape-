/*
 * Ellipse.hpp
 *
 *  Created on: Jun 7, 2010
 *      Author: the-saint
 */

#ifndef ELLIPSE_HPP_
#define ELLIPSE_HPP_

#include <ostream>

#include "../Math/Vector.hpp"

/**
 * @brief A skewed circle.
 */
class Ellipse
{
	public:
	/**
	 * @brief Default constructor.
	 * @param _x The center X position.
	 * @parma _y The center Y position.
	 * @param _xRad The X radius.
	 * @parma _yRad The Y radius.
	 */
	Ellipse(int _x = 0, int _y = 0, unsigned int _xRad = 0, unsigned int _yRad = 0);

	/**
	 * The center position of the ellipse.
	 */
	Vector center;

	/**
	 * The X and Y radii.
	 */
	unsigned int xRad, yRad;
};

/**
 * @brief Adding a vector to an ellipse will increment all vectors of that ellipse by X and Y amount.
 * @param elip The ellipse.
 * @param p The vector.
 * @return The new ellipse.
 * @todo check for how this should look (what is copied, when, and why?)  What would be most efficient here?
 */
Ellipse operator+(Ellipse elip, const Vector& p);

/**
 * @brief Subtracting a vector from an ellipse will decrement all vectors of that ellipse by X and Y amount.
 * @param elip The ellipse.
 * @param p The vector.
 * @return The new ellipse.
 * @todo check for how this should look (what is copied, when, and why?)  What would be most efficient here?
 */
Ellipse operator-(Ellipse elip, const Vector& p);

/**
 * @brief Shift operator to output to an output stream.
 * @param os The output stream.
 * @param elip The ellipse to output.
 */
std::ostream& operator<<(std::ostream& os, const Ellipse& elip);

#endif /* ELLIPSE_HPP_ */
