/*
 * Polygon.hpp
 *
 *  Created on: Apr 8, 2011
 *      Author: the-saint
 */
#ifndef POLYGON_HPP_
#define POLYGON_HPP_

#include "../Math/Vector.hpp"

struct Polygon
{
	/**
	 * Determine the number of vectors in the polygon.
	 * @return The number of vectors.
	 */
	virtual const unsigned int getNumberOfPoints() const = 0;

	/**
	 * Get the specified vector of the polygon.
	 * @param vector The vector to obtain.
	 * @return The vector at the requested position.
	 * @throws std::out_of_range thrown if 'vector' is out of range.
	 */
	virtual Vector getPoint(unsigned int vector) const = 0;

	/**
	 * Calculate an edge.
	 * @param edge The edge position to get (correlates with the vector position)
	 * @return A vector of the vector in the polygon.
	 */
	Vector getEdge(unsigned int edge) const;

	/**
	 * Calculate the center vector of the polygon.
	 * @return The center vector of the polygon.
	 */
	virtual Vector getCenter() const;

	/**
	 * Determine if this polygon is intersecting with another polygon.
	 * @param poly The second polygon.
	 * @return True if an intersection exists.
	 */
	virtual bool isIntersecting(const Polygon& poly) const;

	/**
	 * Determine if this polygon is intersecting with another polygon.
	 * @param poly The second polygon.
	 * @param velocity Reference to a vector that indicates the location this can be placed to be as close as possible to 'poly' if the two would otherwise intersect.
	 * @return True if an intersection exists.
	 */
	virtual bool isIntersecting(const Polygon& poly, Vector& velocity) const;
};

#endif /* POLYGON_HPP_ */
