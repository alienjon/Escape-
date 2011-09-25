/*
 * Point.cpp
 *
 *  Created on: Sep 16, 2011
 *      Author: alienjon
 */
#include "Point.hpp"

using std::ostream;

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
