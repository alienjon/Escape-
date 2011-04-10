/*
 * Vector.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: alienjon
 */
#include "Vector.hpp"

#include <cmath>
#include <stdexcept>

using std::cos;
using std::domain_error;
using std::max;
using std::min;
using std::ostream;
using std::sin;
using std::sqrt;

Vector::Vector(double _x, double _y) : x(_x), y(_y)
{
}

Vector Vector::operator*(double scalar)
{
	return Vector(x * scalar, y * scalar);
}

Vector Vector::operator+(const Vector& pt) const
{
	return Vector(x + pt.x, y + pt.y);
}

Vector Vector::operator-(const Vector& pt) const
{
	return Vector(x - pt.x, y - pt.y);
}

void Vector::rotate(double angle)
{
	double xt = (x * cos(angle)) - (y * sin(angle)),
		   yt = (y * cos(angle)) + (x * sin(angle));
	x = xt;
	y = yt;
}

double Vector::crossProduct(const Vector& pt) const
{
	return (x * pt.y) - (y * pt.x);
}

double Vector::magnitude()
{
	return sqrt(x * x + y * y);
}

void Vector::normalize()
{
	double mag = magnitude();
	if(mag == 0)
		return;
	x /= mag;
	y /= mag;
}

double Vector::dotProduct(const Vector& pt) const
{
	return (x * pt.x) + (y * pt.y);
}

ostream& operator<<(ostream& os, const Vector& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

bool operator==(const Vector& a, const Vector& b)
{
	return (a.x == b.x) && (a.y == b.y);
}

Vector& operator+=(Vector& a, const Vector& b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	return a;
}

Vector& operator-=(Vector& a, const Vector& b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
	return a;
}

Vector operator*(const Vector& vector, double value)
{
	return Vector(vector.x * value, vector.y * value);
}

Vector operator*(double value, const Vector& vector)
{
	return Vector(vector.x * value, vector.y * value);
}

bool doSegmentsIntersect(const Vector& a1, const Vector& a2, const Vector& b1, const Vector& b2)
{
    double aSlope = 0,
           bSlope = 0;
    bool aInfiniteSlope = false,
         bInfiniteSlope = false;
    double aIntersect = 0,
           bIntersect = 0;

    // Get the slopes and intersects.
    try
    {
        aSlope = getSlope(a1, a2);
        aIntersect = getIntercept(a1, aSlope);
    }
    catch(domain_error)
    {
        aInfiniteSlope = true;
    }
    try
    {
        bSlope = getSlope(b1, b2);
        bIntersect = getIntercept(b1, bSlope);
    }
    catch(domain_error)
    {
        bInfiniteSlope = true;
    }

    // If either slope is infinite then we need to handle for a 'special case'.
    if(aInfiniteSlope || bInfiniteSlope)
    {
        double aMin = min(a1.y, a2.y);
        double aMax = max(a1.y, a2.y);
        double bMin = min(b1.y, b2.y);
        double bMax = max(b1.y, b2.y);

        // If both are infinite, then see if the X values match and if they are intersecting within the segments.
        if(aInfiniteSlope && bInfiniteSlope)
        {
            // If the X values don't match, then they don't intersect.
            if(a1.x != b1.x)
            {
                return false;
            }

            // If the x values match, see if the segments overlap on their y values.
            return !(aMin > bMax || aMax < bMin);
        }
        // If only one slope is infinite, then I need to run a 'special case' of finding the vector of intersection.
        else if(aInfiniteSlope)
        {
            // If A.y is infinite but B.y is not, then at what vector on line B does it intersect with A?
            Vector p(a1.x, (bSlope * a1.x) + bIntersect);
            return (p.x > aMin && p.x < aMax) && (p.x > bMin && p.x < bMax);
        }
        else //if(bInfiniteSlope)
        {
            // If B.y is infinite but A.y is not, then at what vector on line A does it intersect with B?
            Vector p(b1.x, (aSlope * b1.x) + aIntersect);
            return (p.x > aMin && p.x < aMax) && (p.x > bMin && p.x < bMax);
        }
    }

    // Get the X min and max values.
    double aMin = min(a1.x, a2.x);
    double aMax = max(a1.x, a2.x);
    double bMin = min(b1.x, b2.x);
    double bMax = max(b1.x, b2.x);

    // If the slopes match...
    if(aSlope == bSlope)
    {
        // ... but the intersects don't match, the segment's can never intersect.
        if(aIntersect != bIntersect)
        {
            return false;
        }

        // Check if the segment's overlap.
        return !(aMin > bMax || aMax < bMin);
    }

    // If the vector rests on in a section within both segments, then we have an intersection.
    Vector p = getVectorOfIntersection(aSlope, aIntersect, bSlope, bIntersect);
    return (p.x > aMin && p.x < aMax) && (p.x > bMin && p.x < bMax);
}

double dotProduct(const Vector& a, const Vector& b)
{
    return (a.x * b.x) + (a.y * b.y);
}

double getDistance(const Vector& p1, const Vector& p2)
{
    return sqrt(pow((p2.y - p1.y), 2) + pow((p2.x - p1.x), 2));
}

double getIntercept(const Vector& p, const int& slope)
{
    return p.y - (slope * p.x);
}

double getInvertedSlope(const double& slope)
{
    if(slope == 0)
    {
        throw domain_error("Zero slope");
    }

    return -1 / slope;
}

Vector getVectorOfIntersection(const double& slopeA, const double& interceptA, const double& slopeB, const double& interceptB)
{
    // If the slopes match then either the 2 lines are exactly the same or will never intersect.
    // Either way, no single vector can be calculated, so return an error.
    if(slopeA == slopeB)
    {
        throw domain_error("Cannot determine single vector: Both lines have matching slopes.");
    }

    // Find the intersecting vector.
    double x = (interceptB - interceptA) / (slopeA - slopeB);
    double y = (slopeA * x) + interceptA;
    return Vector(x, y);
}

Vector getVectorOnLine(const Vector& a, const Vector& b, const int& distance)
{
	// Make sure that a and b are two separate vectors.
	if(a == b)
	{
		return a;
	}

	// The proportion of the distance to the desired vector provided the given two vectors.
	double k = distance / getDistance(a, b);

	// The equation to get the desired vector is: C = A + k(B - A).
	return a + (k * (b - a));
}

double getSlope(const Vector& a, const Vector& b)
{
    // If the X values are equal, then the slope is infinity (a vertical line)
    if(a.x == b.x)
    {
        throw domain_error("Infinite slope");
    }

    return (b.y - a.y) / (b.x - a.x);
}
