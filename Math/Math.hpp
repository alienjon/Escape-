/*
 * Math.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */

#ifndef MATH_HPP_
#define MATH_HPP_

extern const double PI;

#include "../Math/Polygon.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief Converts Radians to Degrees.
 * @param rads The radians.
 * @return The radian value in degrees.
 */
double toDegrees(const double& rads);

/**
 * @brief Converts Degrees to Radians.
 * @param degrees The degrees.
 * @return The degree value in radians.
 */
double toRadians(const double& degrees);

/**
 * Projects a polygon onto a single axis.
 * @param axis The axis is defined by this vector.
 * @param polygon The polygon to project.
 * @param min Reference to the minimum value of the polygon.
 * @param max Reference to the maximum value of the polygon.
 */
void projectPolygonOnSingleAxis(const Vector& axis, const Polygon& polygon, double& min, double& max);

/**
 * Calculates the distance between 2 line segments that exist on a single axis.
 * @param minA The minumum value for the first line.
 * @param maxA The maximum value for the first line.
 * @param minB The minimum value for the second line.
 * @param maxB The maximum value for the second line.
 * @return The distance between both lines (if the lines overlap, then the number will be negative).
 */
double distanceBetweenTwoLineSegments(double minA, double maxA, double minB, double maxB);

#endif /* MATH_HPP_ */
