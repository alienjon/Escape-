/*
 * Direction.cpp
 *
 *  Created on: Aug 10, 2009
 *      Author: alienjon
 */
#include "Direction.hpp"

#include <cmath>
#include <stdexcept>

#include "../Math/Math.hpp"

using std::acos;
using std::logic_error;
using std::string;

Direction directionToPoint(const Vector& pA, const Vector& pB)
{
	// If the points are equal, arbitrarily return a direction.
	if(pA == pB)
	{
		return DIR_DOWN;
	}

	// Determine the angle of the line from pA to pB in radians.
	// This is calculated by finding the arc cosine of line A (if you assume pA to be at the
	//	origin, then it is the distance on the X axis between pA and pB) divided by line B
	// (the distance between pA and pB)
	// @note I convert this to degrees because I'm dumb.
	double angle = toDegrees(acos((pB.x - pA.x) / getDistance(pA, pB)));
	if(pB.y > pA.y) angle = 360 - angle; // After 180o (or PI * rads) the angle is inversed (ie: 190o is actually 170o)  This compensates for that.

	// Determine the direction based on the angle.
	if(angle <= 22.5) return DIR_RIGHT;
	else if(angle <= 67.5) return DIR_UPRIGHT;
	else if(angle <= 112.5) return DIR_UP;
	else if(angle <= 157.5) return DIR_UPLEFT;
	else if(angle <= 202.5) return DIR_LEFT;
	else if(angle <= 247.5) return DIR_DOWNLEFT;
	else if(angle <= 292.5) return DIR_DOWN;
	else if(angle <= 337.5) return DIR_DOWNRIGHT;
	else if(angle <= 360) return DIR_RIGHT;
	else
	{
		throw logic_error("directionToPoint() -> Invalid angle.  Angle is either less than 0 or greater than 360.");
	}
}

string getDirection(Direction dir)
{
    switch(dir)
    {
        case DIR_UP: return "UP";
        case DIR_UPRIGHT: return "UPRIGHT";
        case DIR_RIGHT: return "RIGHT";
        case DIR_DOWNRIGHT: return "DOWNRIGHT";
        case DIR_DOWN: return "DOWN";
        case DIR_DOWNLEFT: return "DOWNLEFT";
        case DIR_LEFT: return "LEFT";
        case DIR_UPLEFT: return "UPLEFT";
        default: return "NULL DIRECTION";
    }
}

Direction getDirection(int n)
{
    switch(n)
    {
        case 0: return DIR_UP;
        case 1: return DIR_UPRIGHT;
        case 2: return DIR_RIGHT;
        case 3: return DIR_DOWNRIGHT;
        case 4: return DIR_DOWN;
        case 5: return DIR_DOWNLEFT;
        case 6: return DIR_LEFT;
        case 7: return DIR_UPLEFT;
        default: return DIR_NONE;
    }
}

Vector getPointInDirection(const Vector& pos, Direction dir, unsigned int dis)
{
	switch(dir)
	{
		case DIR_UP: return Vector(pos.x, pos.y - dis);
		case DIR_UPRIGHT: return Vector(pos.x + dis, pos.y - dis);
		case DIR_RIGHT: return Vector(pos.x + dis, pos.y);
		case DIR_DOWNRIGHT: return Vector(pos.x + dis, pos.y + dis);
		case DIR_DOWN: return Vector(pos.x, pos.y + dis);
		case DIR_DOWNLEFT: return Vector(pos.x - dis, pos.y + dis);
		case DIR_LEFT: return Vector(pos.x - dis, pos.y);
		case DIR_UPLEFT: return Vector(pos.x - dis, pos.y - dis);
		default: return pos;
	}
}

Direction oppositeDirection(Direction facing)
{
    switch(facing)
    {
        case DIR_UP: return DIR_DOWN;
        case DIR_UPRIGHT: return DIR_DOWNLEFT;
        case DIR_RIGHT: return DIR_LEFT;
        case DIR_DOWNRIGHT: return DIR_UPLEFT;
        case DIR_DOWN: return DIR_UP;
        case DIR_DOWNLEFT: return DIR_UPRIGHT;
        case DIR_LEFT: return DIR_RIGHT;
        case DIR_UPLEFT: return DIR_DOWNRIGHT;
        default: return DIR_NONE;
    }
}
