/*
 * Vector.hpp
 *
 *  Created on: Apr 6, 2009
 *      Author: alienjon
 */
#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <ostream>

/**
 * @brief A single, yet specific, vector: x, y coordinate.
 */
struct Vector
{
	public:
	/**
	 * The x and y location.
	 */
	double x, y;

	/**
	 * @brief A vector is a single spot in cartesian space.
	 * @param _x The x location of the vector.
	 * @param _y The y location of the vector.
	 */
	Vector(double _x = 0, double _y = 0);

	/**
	 * Multiply this vector by a scalar.
	 * @param scalar The scalar to multiply the vector by.
	 * @return The vector as multiplied by the scalar.
	 */
	Vector operator*(double scalar);

	/**
	 * Add 2 vectors together.
	 * @param pt The vector to add.
	 * @return The summed vector.
	 */
	Vector operator+(const Vector& pt) const;

	/**
	 * Subtract a vector from this vector.
	 * @param pt The vector to subtract.
	 * @return The updated value.
	 */
	Vector operator-(const Vector& pt) const;

	/**
	 * Rotate the vector around an angle.
	 * @param angle The angle (in degrees).
	 */
	void rotate(double angle);

	/**
	 * Determine the cross product between this vector and another.
	 * @param pt The other vector.
	 * @return The cross product in scalar form.
	 */
	double crossProduct(const Vector& pt) const;

	/**
	 * Calculate the magnitude of this vector.
	 * @return The distance/magnitude of the vector.
	 */
	double magnitude();

	/**
	 * Normalize the vector.
	 * @return The normalized vector.
	 */
	void normalize();

	/**
	 * Find the dot product of this vector and another.
	 * @param pt The other vector.
	 * @return The dot product.
	 */
	double dotProduct(const Vector& pt) const;
};

/**
 * @brief For displaying a vector to the console.
 * @param os The output stream.
 * @param p The vector to output.
 * @return The updated stream.
 */
std::ostream& operator<<(std::ostream& os, const Vector& p);

/**
 * @brief For comparing two vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return True if the two vectors are equal.
 */
bool operator==(const Vector& a, const Vector& b);

/**
 * @brief Add two vectors to determine the vector.
 * @param a The first vector.
 * @param b The second vector.
 * @return The determined vector.
 * @todo check for how this should look (what is copied, when, and why?)  What would be most efficient here?
 */
Vector& operator+=(Vector& a, const Vector& b);

/**
 * @brief Subtract the two vectors to determine the vector (simplified as a vector)
 * @param a The first vector.
 * @param b The second vector.
 * @return The determined vector (Expressed as a vector)
 * @todo check for how this should look (what is copied, when, and why?)  What would be most efficient here?
 */
Vector& operator-=(Vector& a, const Vector& b);

/**
 * @brief Determines if 2 line segments intersect.
 * @param a1 The first vector of line 1.
 * @param a2 The second vector of line 1.
 * @param b1 The first vector of line 2.
 * @param b2 The second vector of line 2.
 * @return True if the two line segments intersect.
 */
bool doSegmentsIntersect(const Vector& a1, const Vector& a2, const Vector& b1, const Vector& b2);

/**
 * @brief Get the distance between 2 vectors.
 * @param p1 The first vector.
 * @param p2 The second vector.
 * @return The distance between both vectors.
 */
double getDistance(const Vector& p1, const Vector& p2);

/**
 * @brief Determine the y-intercept through a vector on a line and that line's slope.
 * @param p The vector on the line.
 * @param slope The slope of the line.
 * @return The y-intercept of the line defined by p and slope.
 */
double getIntercept(const Vector& p, const int& slope);

/**
 * @brief Determine the inverted slope of the provided slope.
 * @param slope
 * @return The slope of a line that will be perpendicular to the slope provided.
 */
double getInvertedSlope(const double& slope);

/**
 * @brief Determine the vector of intersection between 2 lines.
 * @param slopeA The slope of the first line.
 * @param interceptA The y-intercept of the first line.
 * @param slopeB The slope of the second line.
 * @param interceptB The y-intercept of the second line.
 * @return The intersecting vector.
 * @throws A domain error if the slopes match.
 */
Vector getVectorOfIntersection(const double& slopeA, const double& interceptA, const double& slopeB, const double& interceptB);

/**
 * @brief Get a vector on a line at a certain distance from an origin vector.
 * @param a The originating vector.
 * @param b A second vector on the line in the direction of the desired vector.
 * @param distance The distance on the line from the originating vector that the desired vector resides.
 * @return The vector on the line at a given distance from the originating vector.
 */
Vector getVectorOnLine(const Vector& a, const Vector& b, const int& distance);

/**
 * @brief Determine's the slope of the line determined by two vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return The slope of the line determined by a -> b.
 */
double getSlope(const Vector& a, const Vector& b);

#endif /* VECTOR_HPP_ */
