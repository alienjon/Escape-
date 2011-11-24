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

sf::FloatRect boundingBox(const sf::Shape& shape)
{
	if(shape.GetPointsCount() == 0)
		return sf::FloatRect();

	int xMin = 0, xMax = 0, yMin = 0, yMax = 0;
	for(unsigned int i = 0; i != shape.GetPointsCount(); ++i)
	{
		if(shape.GetPointPosition(i).x < xMin)
			xMin = shape.GetPointPosition(i).x;
		if(shape.GetPointPosition(i).x > xMax)
			xMax = shape.GetPointPosition(i).x;
		if(shape.GetPointPosition(i).y < yMin)
			yMin = shape.GetPointPosition(i).y;
		if(shape.GetPointPosition(i).y > yMax)
			yMax = shape.GetPointPosition(i).y;
	}
	return sf::FloatRect(xMin, yMin, xMax - xMin, yMax - yMin);
}

sf::Vector2f center(const sf::Shape& shape)
{
	float x = 0, y = 0;
	for(unsigned int i = 0; i != shape.GetPointsCount(); ++i)
	{
		x += shape.GetPointPosition(i).x;
		y += shape.GetPointPosition(i).y;
	}
	x /= shape.GetPointsCount();
	y /= shape.GetPointsCount();
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

sf::Vector2f edge(const sf::Shape& poly, unsigned int edge)
{
	sf::Vector2f a = poly.GetPointPosition(edge),
				 b = (edge + 1 == poly.GetPointsCount()) ? poly.GetPointPosition(0) : poly.GetPointPosition(edge + 1);
	return b - a;
}

bool isPolyIntersecting(sf::Shape poly1, sf::Shape poly2)
{
	for(unsigned int i = 0; i != poly1.GetPointsCount(); ++i)
		poly1.SetPointPosition(i, poly1.GetPointPosition(i) + poly1.GetPosition());
	for(unsigned int i = 0; i != poly2.GetPointsCount(); ++i)
		poly2.SetPointPosition(i, poly2.GetPointPosition(i) + poly2.GetPosition());
	int pointCountA = poly1.GetPointsCount(),
		pointCountB = poly2.GetPointsCount();
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

void projectPolygonOnSingleAxis(const sf::Vector2f& axis, const sf::Shape& polygon, float& min, float& max)
{
	float dotP = dotProduct(axis, polygon.GetPointPosition(0));
	min = max = dotP;
	for(unsigned int i = 0; i != polygon.GetPointsCount(); ++i)
	{
		dotP = dotProduct(polygon.GetPointPosition(i), axis);
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
