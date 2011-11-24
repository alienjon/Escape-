///*
// * Quadrilateral.cpp
// *
// *  Created on: Apr 6, 2009
// *      Author: alienjon
// */
//
//#include "Quadrilateral.hpp"
//
//#include <cmath>
//#include <stdexcept>
//
//#include "../Math/Math.hpp"
//#include "../Math/Rectangle.hpp"
//
//using std::abs;
//using std::acos;
//using std::asin;
//using std::cos;
//using std::domain_error;
//using std::ostream;
//using std::out_of_range;
//using std::sin;
//
//Quadrilateral::Quadrilateral()
//{
//}
//
//Quadrilateral::Quadrilateral(const Rectangle& rect) :
//	p1(rect.vector.x, rect.vector.y),
//	p2(rect.vector.x + rect.width, rect.vector.y),
//	p3(rect.vector.x + rect.width, rect.vector.y + rect.height),
//	p4(rect.vector.x, rect.vector.y + rect.height)
//{
//}
//
//Quadrilateral::Quadrilateral(const Vector& _p1, const Vector& _p2, const Vector& _p3, const Vector& _p4) :
//	p1(_p1),
//	p2(_p2),
//	p3(_p3),
//	p4(_p4)
//{
//}
//
//Rectangle Quadrilateral::getBoundingBox() const
//{
//    // Get the min and max for this and the checking quadrilateral.
//    int thisXMin = (p1.x < p2.x) ? p1.x : p2.x;
//    thisXMin = (thisXMin < p3.x) ? thisXMin : p3.x;
//    thisXMin = (thisXMin < p4.x) ? thisXMin : p4.x;
//    int thisXMax = (p1.x > p2.x) ? p1.x : p2.x;
//    thisXMax = (thisXMax > p3.x) ? thisXMax : p3.x;
//    thisXMax = (thisXMax > p4.x) ? thisXMax : p4.x;
//    int thisYMin = (p1.y < p2.y) ? p1.y : p2.y;
//    thisYMin = (thisYMin < p3.y) ? thisYMin : p3.y;
//    thisYMin = (thisYMin < p4.y) ? thisYMin : p4.y;
//    int thisYMax = (p1.y > p2.y) ? p1.y : p2.y;
//    thisYMax = (thisYMax > p3.y) ? thisYMax : p3.y;
//    thisYMax = (thisYMax > p4.y) ? thisYMax : p4.y;
//
//    return Rectangle(thisXMin, thisYMin, thisXMax - thisXMin, thisYMax - thisYMin);
//}
//
//const unsigned int Quadrilateral::getNumberOfPoints() const
//{
//	return 4;
//}
//
//Vector Quadrilateral::getPoint(unsigned int point) const
//{
//	switch(point)
//	{
//		case 0: return p1;
//		case 1: return p2;
//		case 2: return p3;
//		case 3: return p4;
//		default: throw out_of_range("Quadrilateal::getPoint() -> Point requested is out of range.");
//	}
//}
//
//bool Quadrilateral::isVectorInside(const Vector& vector) const
//{
//	bool oddNodes = false;
//
//	// See if the vector crosses the first line.
//	if((p1.y < vector.y && p4.y >= vector.y) || (p4.y < vector.y && p1.y >= vector.y))
//	{
//		if(p1.x + (vector.y - p1.y) / (p4.y - p1.y) * (p4.x - p1.x < vector.x))
//		{
//			oddNodes = !oddNodes;
//		}
//	}
//
//	// See if the vector crosses the second line.
//	if((p2.y < vector.y && p1.y >= vector.y) || (p1.y < vector.y && p2.y >= vector.y))
//	{
//		if(p2.x + (vector.y - p2.y) / (p1.y - p2.y) * (p1.x - p2.x < vector.x))
//		{
//			oddNodes = !oddNodes;
//		}
//	}
//
//	// See if the vector crosses the third line.
//	if((p3.y < vector.y && p2.y >= vector.y) || (p2.y < vector.y && p3.y >= vector.y))
//	{
//		if(p3.x + (vector.y - p3.y) / (p2.y - p3.y) * (p2.x - p3.x < vector.x))
//		{
//			oddNodes = !oddNodes;
//		}
//	}
//
//	// See if the vector crosses the fourth line.
//	if((p4.y < vector.y && p3.y >= vector.y) || (p3.y < vector.y && p4.y >= vector.y))
//	{
//		if(p4.x + (vector.y - p4.y) / (p3.y - p4.y) * (p3.x - p4.x < vector.x))
//		{
//			oddNodes = !oddNodes;
//		}
//	}
//
//	return oddNodes;
//}
//
//Quadrilateral operator+(Quadrilateral quad, const Vector& p)
//{
//	quad.p1 += p;
//	quad.p2 += p;
//	quad.p3 += p;
//	quad.p4 += p;
//	return quad;
//}
//
//Quadrilateral operator-(Quadrilateral quad, const Vector& p)
//{
//	quad.p1 -= p;
//	quad.p2 -= p;
//	quad.p3 -= p;
//	quad.p4 -= p;
//	return quad;
//}
//
//ostream& operator<<(ostream& os, const Quadrilateral& quad)
//{
//    os << "[" << quad.p1 << ":" << quad.p2 << ":" << quad.p3 << ":" << quad.p4 << "]";
//    return os;
//}
//
//Quadrilateral getIsoscelesTrapezoid(const Vector& baseVector, const Vector& distanceVector, unsigned int distance, unsigned int baseSpan, unsigned int farSpan)
//{
//	/**
//	 * To find the 4 vectors of this trapezoid consider the following:
//	 *
//	 * The line that runs through the base vector and the distance vector acts as both the altitude of the trapezoid
//	 * as well as its line of symmetry (it is exactly in the middle of the shape such that if you folded it in half
//	 * over this line it would be exactly half the shape).  This line is defined by baseVector and distanceVector.
//	 *
//	 * The size of the altitude, however, is the parameter 'distance' and the first step in finding the 4 vectors is
//	 * to find this far_side_vector (far side, if one considers the first parameter (the base) as the starting vector
//	 * of the quadrilateral).
//	 *
//	 * Once this vector is known then reconsider the baseVector and the far_side_vector as creating the hypoteneuse of
//	 * a right triangle (the third vector of which could be in 2 different locations, therefore resulting in 2 different
//	 * triangles, but both triangles would be identical in regards to their angles and sides so differentiating between
//	 * them is not necessary here).  To define this triangle, consider the line baesVector->far_side_vector as the
//	 * hypoteneuse, the baseVector as main_angle_a, far_side_vector as main_angle_b and the right angle (which, again,
//	 * could be in two locations) as main_angle_c.  main_angle_c's coordinates can be calculated by finding the absolute value of
//	 * the difference between main_angle_a's and main_angle_b's x and y coordinates (absolute value because a distance
//	 * cannot be negative - or at least not in this consideration).  main_angle_c's coordinates, then, are:
//	 * main_angle_c = (main_angle_b.x - main_angle_a.x, main_angle_b.y - main_angle_a.y).
//	 *
//	 * For our purposes, only one of these sides is required to find the angles and, from there, the smaller right triangles
//	 * that define the 4 vectors for which we are looking.  I arbitrarily picked side A (therefore the side opposite
//	 * the angle of our baseVector and whose length is main_angle_b.y - main_angle_a.y).  To find the size of main_angle_a
//	 * in radians we would calculate sine(main_angle_a) = main_side_a / main_side_c (sine(x) = opposite/hypoteneuse). To solve
//	 * for main_angle_a (what we are looking for) we would need to find the inverse function of sine (arcsine).  The
//	 * calculation then transforms into main_angle_a = arcsine(main_side_a / main_side_c).  <cmath> provides all the trig
//	 * functions needed to perform this calculation, but works with radians.  Therefore we need to do a conversion
//	 * to get the degree value for which we are looking.
//	 *
//	 * Although I won't talk about it for a little bit, we also need to get main_angle_b, and its calculations are fairly
//	 * similar, but we are using cosine instead of sine (unless we wanted to calculate main_side_b, but since we already
//	 * have main_side_a this isn't necessarily).  Basically, cosine(main_angle_b) = main_side_a / main_side_c
//	 * (cosine(x) = adjacent/hypoteneuse).  Considering the inverse to solidify the angle, we are left with:
//	 * main_angle_b = arccos(main_side_a / main_side_c).  Once again this value needs to be converted to degrees from radians.
//	 *
//	 * Back to baseVector.  If we now reconsider baseVector to be angleA of a smaller right triangle whose angleB is at the
//	 * coordinate we are looking for our first vector, then we can create another right triangle, whose hypoteneuse is defined
//	 * by vectors base_1_angle_a (the same vector as main_angle_a - note that though it is the same vector, the angle of this
//	 * new triangle is probably not the same as main_angle_a, so it needs to be calculated), base_1_angle_b (this is the angle
//	 * at the coordinate for which we are looking), and base_1_angle_c (this is the right angle of this smaller triangle.
//	 *
//	 * Note the remainder of this explanation will be identical with the vectors and angles changed based on which of the 4
//	 * trapezoid vectors towards which we are working.  This, for example, is why I have listed the first smaller triangle as
//	 * 'base_1' (ie: base_1_angle_a, base_1_side_b).  base_1_* refers to the first vector of the trapezoid, far_1_* to the
//	 * second, far_2_* to the third, and base_2_* to the fourth.  That having been said, for this reason I will only calculate
//	 * this first triangle, but the logic is the same for the other 4.
//	 *
//	 * Now, again, back to baseVector - or, more specifically, triangle base_1.  Remember our original symmetrical line through
//	 * the trapezoid?  As this is the altitude of the shape it intersects both sides of the shape at 90o angles.  If we also
//	 * consider that main_side_b (the one we did not calculate) and continued it through main_angle_a, then we see that this
//	 * line is made up of main_angle_a, the right angle of the altitude and, on the other side of these, base_1_angle_a.  This
//	 * means that this line is equal to all three angles or, specifically: main_angle_a + base_1_angle_a + 90 = 180.  Flippin'
//	 * stuff around and we now have: base_1_angle_a = 90 - main_angle_a.
//	 *
//	 * From here we can calculate all three sides.  First, the hypoteneuse, which is actually provided as function parameter:
//	 * 'baseSpan'.  As baseSpan is the full length of the base side of the trapezoid, half of it exists as the hypoteneuse of
//	 * the base triangles.  In other words, the hypoteneuse of both base_1_* and base_2_* is baseSpan / 2 (which I'll refer to
//	 * now as base_1_side_c and base_2_side_c).  base_1_side_a is calculated from sine(base_1_angle_a) = base_1_side_a / base_1_side_c.
//	 * Or, if converted: base_1_side_a = sine(base_1_angle_a) * base_1_side_c.  base_1_side_b is calculated with cosine, so:
//	 * cos(base_1_angle_a) = base_1_side_b / base_1_side_c and this is converted to: base_1_side_b = cos(base_1_angle_a) * base_1_side_c.
//	 *
//	 * So we now have the lengths of the three sides of triangle base_1_*.  The coordinate we are looking for is of an x
//	 * distance of base_1_side_b and a y distance of base_1_side_a from the baseVector.  The tricky part here is to determine
//	 * if these values are added or subtracted from the baseVector to determine the actual coordinate of the vector.  This is
//	 * tricky because it will depend on the direction the quadrilateral is facing (baseVector->far_vector).  If the quadrilateral
//	 * is facing straight up, for example, then the x value is subtracted from baseVector.x because the first vector is to the left.
//	 * If it was face down then it would be added together because the vector is to the right.  To further complicate things since
//	 * this is going to be used in computer graphics the Y coordinates are inverted, such that +y is downwards, not upwards.  This
//	 * means that if the quadrilateral is facing to the right (the far_side is on the right-hand side of the screen) then the
//	 * first vector's y axis will be subtracted from the baseVector instead of added even though it is going down the y-axis.
//	 * Conversely, if the quadrilateral was facing left then the vector would move down the y-axis, but would be added instead
//	 * of subtracted.
//	 *
//	 * As it was already mentioned, this process should be repeated for each of the 4 vectors.
//	 */
//	// The far side vector.
//	Vector far_vector = getVectorOnLine(baseVector, distanceVector, distance);
//
//	// xCord is positive if distance vector is to the right of the base vector and negative otherwise.
//	// yCord is positive if distance vector is above the baes vector and negative otherwise.
//	const int xSign = (far_vector.x > baseVector.x) ? 1 : -1,
//			  ySign = (far_vector.y > baseVector.y) ? 1 : -1;
//
//	// This whole calculation gets angle A from the main triangle in degrees.
//	double main_angle_a = toDegrees(asin(abs(far_vector.y - baseVector.y) / distance)),
//		   main_angle_b = toDegrees(acos(abs(far_vector.y - baseVector.y) / distance));
//
//	// These are the A angles of the 4 triangles.
//	double base_1_angle_a = 90 - main_angle_a,
//		   base_2_angle_a = 90 - main_angle_b, // This is a shortcut and should work because the base_2_angle_a's 90o complimentary angle is congruant to main_angle_b (draw it out and you'll see)
//		   far_1_angle_b  = 90 - main_angle_b,
//		   far_2_angle_b  = 90 - main_angle_a; // See the note for base_2_angle_a above.  The same logic should work here.
//
//	// The sides of all 4 smaller triangles - note that the sides do not correspond with an X,Y value (ie: *side_a could be either the X or Y coordinate, depending on the vector)
//	double base_1_side_a = sin(toRadians(base_1_angle_a)) * (baseSpan / 2), // Vector 1 Y
//		   base_1_side_b = cos(toRadians(base_1_angle_a)) * (baseSpan / 2), // Vector 1 X
//		   base_2_side_a = sin(toRadians(base_2_angle_a)) * (baseSpan / 2), // Vector 4 X
//		   base_2_side_b = cos(toRadians(base_2_angle_a)) * (baseSpan / 2), // Vector 4 Y
//		   far_1_side_a  = cos(toRadians(far_1_angle_b))  * (farSpan  / 2), // Vector 2 Y
//		   far_1_side_b  = sin(toRadians(far_1_angle_b))  * (farSpan  / 2), // Vector 2 X
//		   far_2_side_a  = cos(toRadians(far_2_angle_b))  * (farSpan  / 2), // Vector 3 X
//		   far_2_side_b  = sin(toRadians(far_2_angle_b))  * (farSpan  / 2); // Vector 3 Y
//
//	// Now calculate the vectors.  xSign and ySign are used to determine if the side values should be added or subtracted from
//	// their base vectors.
//	Vector vectorA(baseVector.x + (base_1_side_b * xSign), baseVector.y - (base_1_side_a * ySign)),
//		  vectorB(far_vector.x + (far_1_side_b  * xSign), far_vector.y - (far_1_side_a  * ySign)),
//		  vectorC(far_vector.x - (far_2_side_a  * xSign), far_vector.y + (far_2_side_b  * ySign)),
//		  vectorD(baseVector.x - (base_2_side_a * xSign), baseVector.y + (base_2_side_b * ySign));
//
//	return Quadrilateral(vectorA, vectorB, vectorC, vectorD);
//}
