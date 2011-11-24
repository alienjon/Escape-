//struct Vector@todo still using any of these?
//{
//	/**
//	 * Rotate the vector around an angle.
//	 * @param angle The angle (in degrees).
//	 */
//	void rotate(double angle);
//
//	/**
//	 * Determine the cross product between this vector and another.
//	 * @param pt The other vector.
//	 * @return The cross product in scalar form.
//	 */
//	double crossProduct(const Vector& pt) const;
//};
//
///**
// * @brief Determines if 2 line segments intersect.
// * @param a1 The first vector of line 1.
// * @param a2 The second vector of line 1.
// * @param b1 The first vector of line 2.
// * @param b2 The second vector of line 2.
// * @return True if the two line segments intersect.
// */
//bool doSegmentsIntersect(const Vector& a1, const Vector& a2, const Vector& b1, const Vector& b2);
//
///**
// * @brief Get the distance between 2 vectors.
// * @param p1 The first vector.
// * @param p2 The second vector.
// * @return The distance between both vectors.
// */
//double getDistance(const Vector& p1, const Vector& p2);
//
///**
// * @brief Determine the y-intercept through a vector on a line and that line's slope.
// * @param p The vector on the line.
// * @param slope The slope of the line.
// * @return The y-intercept of the line defined by p and slope.
// */
//double getIntercept(const Vector& p, const int& slope);
//
///**
// * @brief Determine the inverted slope of the provided slope.
// * @param slope
// * @return The slope of a line that will be perpendicular to the slope provided.
// */
//double getInvertedSlope(const double& slope);
//
///**
// * @brief Determine the vector of intersection between 2 lines.
// * @param slopeA The slope of the first line.
// * @param interceptA The y-intercept of the first line.
// * @param slopeB The slope of the second line.
// * @param interceptB The y-intercept of the second line.
// * @return The intersecting vector.
// * @throws A domain error if the slopes match.
// */
//Vector getVectorOfIntersection(const double& slopeA, const double& interceptA, const double& slopeB, const double& interceptB);
//
///**
// * @brief Get a vector on a line at a certain distance from an origin vector.
// * @param a The originating vector.
// * @param b A second vector on the line in the direction of the desired vector.
// * @param distance The distance on the line from the originating vector that the desired vector resides.
// * @return The vector on the line at a given distance from the originating vector.
// */
//Vector getVectorOnLine(const Vector& a, const Vector& b, const int& distance);
//
///**
// * @brief Determine's the slope of the line determined by two vectors.
// * @param a The first vector.
// * @param b The second vector.
// * @return The slope of the line determined by a -> b.
// */
//double getSlope(const Vector& a, const Vector& b);
//
//#endif /* VECTOR_HPP_ */
