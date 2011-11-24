///*
// * Quadrilateral.hpp
// *
// *  Created on: Apr 6, 2009
// *      Author: alienjon
// */
//@todo still using quads?
//#ifndef QUADRILATERAL_HPP
//#define QUADRILATERAL_HPP
//
//#include <ostream>
//
//#include "../Math/Polygon.hpp"
//#include "../Math/Rectangle.hpp"
//#include "../Math/Vector.hpp"
//
///**
// * @brief Any shape with 4 vectors.
// *
// * The quadrilateral is mainly used as a means for enemies to search for victims.
// */
//struct Quadrilateral : public Polygon
//{
//	public:
//	/**
//	 * The four coordinates.
//	 */
//	Vector p1, p2, p3, p4;
//
//	/**
//	 * @brief A quadrilateral with all vectors initialized to zero.
//	 */
//	Quadrilateral();
//
//	/**
//	 * @brief Create a quadrilateral from a rectangle.
//	 * @param rect The rectangle.
//	 */
//	Quadrilateral(const Rectangle& rect);
//
//	/**
//	 * @brief A quadrilateral is defined as a geometric shape that is made up of 4 vectors.
//	 * @param _p1 The first vector.
//	 * @param _p2 The second vector.
//	 * @param _p3 The third vector.
//	 * @param _p4 The fourth vector.
//	 */
//	Quadrilateral(const Vector& _p1, const Vector& _p2, const Vector& _p3, const Vector& _p4);
//
//	/**
//	 * @brief Get the bounding box of this quadrilateral.
//	 * @return An rectangle that exactly encompasses this quadrilateral.
//	 */
//	Rectangle getBoundingBox() const;
//
//	/**
//	 * Determine the number of vectors in the polygon.
//	 * @return The number of vectors.
//	 */
//	virtual const unsigned int getNumberOfPoints() const;
//
//	/**
//	 * Get the specified vector of the polygon.
//	 * @param point The point to obtain.
//	 * @return The vector at the requested position.
//	 * @throws std::out_of_range thrown if 'vector' is out of range.
//	 */
//	virtual Vector getPoint(unsigned int point) const;
//
//	/**
//	 * @brief Checks if a vector is within this quadrilateral.
//	 * @param vector The vector to search for.
//	 * @return True if the vector is inside this quadrilateral.
//	 */
//	bool isVectorInside(const Vector& vector) const;
//};
//
///**
// * @brief Adding a vector to a quadrilateral will increment all vectors of that quadrilateral by X and Y amount.
// * @param quad The quadrilateral.
// * @param p The vector.
// * @return The updated quadrilateral.
// */
//Quadrilateral operator+(Quadrilateral quad, const Vector& p);
//
///**
// * @brief Subtracting a vector from a quadrilateral will decrement all vectors of that quadrilateral by X and Y amount.
// * @param quad The quadrilateral.
// * @param p The vector.
// * @return The updated quadrilateral.
// */
//Quadrilateral operator-(Quadrilateral quad, const Vector& p);
//
///**
// * @brief External function for outputting the dimensions of a quadrilateral.
// * @param os The stream to output to.
// * @param quad The quadrilateral to output.
// * @return The updated stream.
// */
//std::ostream& operator<<(std::ostream& os, const Quadrilateral& quad);
//
///**
// * @brief Generate an isosceles trapezoid who is defined by the following properties.
// * @param baseVector a vector in the center of the base side.
// * @param distanceVector The vector on the line that will cut the trapezoid in half.
// * @param distance The distance between the two sides. (not necessarily the distance between baseVector and distanceVector)
// * @param baseSpan The length of the base side.
// * @param farSpan The length of the far side.
// * @return The defined quadrilateral.
// */
//Quadrilateral getIsoscelesTrapezoid(const Vector& baseVector, const Vector& distanceVector, unsigned int distance, unsigned int baseSpan, unsigned int farSpan);
//
//#endif /* QUADRILATERAL_HPP */
