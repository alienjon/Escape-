/*
 * Math.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */
#include "Math.hpp"

const double PI = 3.14159265;

double toDegrees(const double& rads)
{
	return rads * 180 / PI;
}

double toRadians(const double& degrees)
{
	return degrees * PI / 180;
}

void projectPolygonOnSingleAxis(const Vector& axis, const Polygon& polygon, double& min, double& max)
{
	double dotP = axis.dotProduct(polygon.getPoint(0));
	min = max = dotP;
	for(unsigned int i = 0; i != polygon.getNumberOfPoints(); ++i)
	{
		dotP = polygon.getPoint(i).dotProduct(axis);
		if(dotP < min) min = dotP;
		else if(dotP > max) max = dotP;
	}
}

double distanceBetweenTwoLineSegments(double minA, double maxA, double minB, double maxB)
{
	return (minA < minB) ? minB - maxA : minA - maxB;
}
