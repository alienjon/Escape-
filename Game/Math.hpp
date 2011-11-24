/*
 * Math.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */
#ifndef MATH_HPP_
#define MATH_HPP_

extern const float PI;

#include <SFML/Graphics.hpp>

/**
 * @brief Calculate the bounding box of a shape.
 * @param shape The shape to calculate.
 * @return The bounding box.
 */
sf::FloatRect boundingBox(const sf::Shape& shape);

/**
 * Calculate the center vector of the polygon.
 * @param shape The shape to get the center of.
 * @return The center vector of the polygon.
 */
sf::Vector2f center(const sf::Shape& shape);

/**
 * Calculates the distance between 2 line segments that exist on a single axis.
 * @param minA The minumum value for the first line.
 * @param maxA The maximum value for the first line.
 * @param minB The minimum value for the second line.
 * @param maxB The maximum value for the second line.
 * @return The distance between both lines (if the lines overlap, then the number will be negative).
 */
float distanceBetweenTwoLineSegments(float minA, float maxA, float minB, float maxB);

/**
 * Find the dot product of 2 vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The dot product.
 */
float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

/**
 * Calculate an edge.
 * @param poly The shape to calculate an edge.
 * @param edge The edge position to get (correlates with the vector position)
 * @return A vector of the vector in the polygon.
 */
sf::Vector2f edge(const sf::Shape& poly, unsigned int edge);

/**
 * Determine if 2 polygons are intersecting.
 * @param poly1 The first polygon.
 * @param poly2 The second polygon.
 * @return True if an intersection exists.
 */
bool isPolyIntersecting(sf::Shape poly1, sf::Shape poly2);

/**
 * Calculate the magnitude of this vector.
 * @param vec The vector.
 * @return The distance/magnitude of the vector.
 */
float magnitude(const sf::Vector2f& vec);

/**
 * Normalize a vector.
 * @param vec The original vector.
 * @return The normalized vector.
 */
sf::Vector2f normalize(const sf::Vector2f& vec);

/**
 * Projects a polygon onto a single axis.
 * @param axis The axis is defined by this vector.
 * @param polygon The polygon to project.
 * @param min Reference to the minimum value of the polygon.
 * @param max Reference to the maximum value of the polygon.
 */
void projectPolygonOnSingleAxis(const sf::Vector2f& axis, const sf::Shape& polygon, float& min, float& max);

/**
 * @brief Converts Radians to Degrees.
 * @param rads The radians.
 * @return The radian value in degrees.
 */
float toDegrees(float rads);

/**
 * @brief Converts Degrees to Radians.
 * @param degrees The degrees.
 * @return The degree value in radians.
 */
float toRadians(float degrees);

#endif /* MATH_HPP_ */
