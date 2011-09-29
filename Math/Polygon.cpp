/*
 * Polygon.cpp
 *
 *  Created on: Apr 8, 2011
 *      Author: the-saint
 */
#include "Polygon.hpp"

#include "../Math/Math.hpp"

Vector Polygon::getEdge(unsigned int edge) const
{
	Vector a = getPoint(edge),
		   b = (edge + 1 == getNumberOfPoints()) ? getPoint(0) : getPoint(edge + 1);
	return b - a;
}

Vector Polygon::getCenter() const
{
	double x = 0, y = 0;
	for(unsigned int i = 0; i != getNumberOfPoints(); ++i)
	{
		x += getPoint(i).x;
		y += getPoint(i).y;
	}
	x /= getNumberOfPoints();
	y /= getNumberOfPoints();
	return Vector(x, y);
}

bool Polygon::isIntersecting(const Polygon& poly) const
{
	int pointCountA = getNumberOfPoints(),
		pointCountB = poly.getNumberOfPoints();
	int totalPoints = pointCountA + pointCountB;

	// Loop through all Points.
	for(int pointIndex = 0; pointIndex != totalPoints; ++pointIndex)
	{
		// Get the current Vector.
		Vector edge = (pointIndex < pointCountA) ? getEdge(pointIndex) : poly.getEdge(pointIndex - pointCountA);

		// Are the polygons intersecting now?
		Vector axis = Vector(-edge.y, edge.x);
		axis.normalize();
		double minA = 0, maxA = 0, minB = 0, maxB = 0;
		projectPolygonOnSingleAxis(axis, *this, minA, maxA);
		projectPolygonOnSingleAxis(axis, poly,  minB, maxB);

		if(distanceBetweenTwoLineSegments(minA, maxA, minB, maxB) >= 0)
		{
			return false;
		}
	}

	// No separating axis found, the polygons must intersect.
	return true;
}

bool Polygon::isIntersecting(const Polygon& poly, Vector& velocity) const
{
	return isIntersecting(poly);//@todo implement velocity setting (need to change to non-const Polygon& ?
}
