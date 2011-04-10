/*
 * Ellipse.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: the-saint
 */

#include "Ellipse.hpp"

using std::ostream;

Ellipse::Ellipse(int _x, int _y, unsigned int _xRad, unsigned int _yRad) :
	center(_x, _y),
	xRad(_xRad),
	yRad(_yRad)
{
}

Ellipse operator+(Ellipse elip, const Vector& p)
{
	elip.center += p;
	return elip;
}

Ellipse operator-(Ellipse elip, const Vector& p)
{
	elip.center -= p;
	return elip;
}

ostream& operator<<(ostream& os, const Ellipse& elip)
{
	os << '[' << elip.center << ':' << elip.xRad << ", " << elip.yRad;
	return os;
}
