/*
 * Math.cpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */
#include "Math.hpp"

#include <cmath>

using std::sqrt;

const float PI = 3.14159265f;

sf::FloatRect boundingBox(const sf::ConvexShape& shape)
{
	if(shape.getPointCount() == 0)
		return sf::FloatRect();

	int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
	for(unsigned int i = 0; i != shape.getPointCount(); ++i)
	{
		if(shape.getPoint(i).x < xMin)
			xMin = shape.getPoint(i).x;
		if(shape.getPoint(i).x > xMax)
			xMax = shape.getPoint(i).x;
		if(shape.getPoint(i).y < yMin)
			yMin = shape.getPoint(i).y;
		if(shape.getPoint(i).y > yMax)
			yMax = shape.getPoint(i).y;
	}
	return sf::FloatRect(xMin, yMin, xMax - xMin, yMax - yMin);
}

sf::Vector2f center(const sf::ConvexShape& shape)
{
	float x = 0, y = 0;
	for(unsigned int i = 0; i != shape.getPointCount(); ++i)
	{
		x += shape.getPoint(i).x;
		y += shape.getPoint(i).y;
	}
	x /= shape.getPointCount();
	y /= shape.getPointCount();
	return sf::Vector2f(x, y);
}

float distanceBetweenTwoLineSegments(float minA, float maxA, float minB, float maxB)
{
	return (minA < minB) ? minB - maxA : minA - maxB;
}

float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

sf::Vector2f edge(const sf::ConvexShape& poly, unsigned int edge)
{
	sf::Vector2f a = poly.getPoint(edge),
				 b = (edge + 1 == poly.getPointCount()) ? poly.getPoint(0) : poly.getPoint(edge + 1);
	return b - a;
}

bool isPolyIntersecting(sf::ConvexShape poly1, sf::ConvexShape poly2)
{
	for(unsigned int i = 0; i != poly1.getPointCount(); ++i)
		poly1.setPoint(i, poly1.getPoint(i) + poly1.getPosition());
	for(unsigned int i = 0; i != poly2.getPointCount(); ++i)
		poly2.setPoint(i, poly2.getPoint(i) + poly2.getPosition());
	int pointCountA = poly1.getPointCount(),
		pointCountB = poly2.getPointCount();
	int totalPoints = pointCountA + pointCountB;

	// Loop through all Points.
	for(int pointIndex = 0; pointIndex != totalPoints; ++pointIndex)
	{
		// Get the current Vector.
		sf::Vector2f _edge = (pointIndex < pointCountA) ? edge(poly1, pointIndex) : edge(poly2, pointIndex - pointCountA);

		// Are the polygons intersecting now?
		sf::Vector2f axis = normalize(sf::Vector2f(-_edge.y, _edge.x));
		float minA = 0, maxA = 0, minB = 0, maxB = 0;
		projectPolygonOnSingleAxis(axis, poly1, minA, maxA);
		projectPolygonOnSingleAxis(axis, poly2, minB, maxB);

		if(distanceBetweenTwoLineSegments(minA, maxA, minB, maxB) >= 0)
			return false;
	}

	// No separating axis found, the polygons must intersect.
	return true;
}

float magnitude(const sf::Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f normalize(const sf::Vector2f& vec)
{
	float mag = magnitude(vec);
	if(mag == 0)
		return vec;
	return sf::Vector2f(vec.x / mag, vec.y / mag);
}

void projectPolygonOnSingleAxis(const sf::Vector2f& axis, const sf::ConvexShape& polygon, float& min, float& max)
{
	float dotP = dotProduct(axis, polygon.getPoint(0));
	min = max = dotP;
	for(unsigned int i = 0; i != polygon.getPointCount(); ++i)
	{
		dotP = dotProduct(polygon.getPoint(i), axis);
		if(dotP < min) min = dotP;
		else if(dotP > max) max = dotP;
	}
}

float toDegrees(float rads)
{
	return rads * 180 / PI;
}

float toRadians(float degrees)
{
	return degrees * PI / 180;
}
