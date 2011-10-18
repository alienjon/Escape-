/*
 * Rectangle.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: alienjon
 */
#include "Rectangle.hpp"

#include <stdexcept>

#include "Quadrilateral.hpp"

using std::ostream;
using std::out_of_range;

Rectangle::Rectangle(double _x, double _y, unsigned int _w, unsigned int _h) :
	vector(_x, _y),
	width(_w),
	height(_h)
{}

Rectangle::Rectangle(const gcn::Rectangle& rect) :
	vector(rect.x, rect.y),
	width(rect.width),
	height(rect.height)
{}

Rectangle::Rectangle(const gcn::ClipRectangle& rect) :
	vector(rect.x, rect.y),
	width(rect.width),
	height(rect.height)
{}

Rectangle::Rectangle(const SDL_Rect& rect) :
	vector(rect.x, rect.y),
	width(rect.w),
	height(rect.h)
{}

Rectangle::operator gcn::Rectangle()
{
    return gcn::Rectangle(vector.x, vector.y, width, height);
}

Vector Rectangle::getCenter() const
{
    return Vector(vector.x + (width / 2), vector.y + (height / 2));
}

const unsigned int Rectangle::getNumberOfPoints() const
{
	return 4;
}

Vector Rectangle::getPoint(unsigned int point) const
{
	switch(point)
	{
		case 0: return vector;
		case 1: return Vector(vector.x + width, vector.y);
		case 2: return Vector(vector.x + width, vector.y + height);
		case 3: return Vector(vector.x, vector.y + height);
		default: throw out_of_range("Rectangle::getVector() -> Vector requested is out of range.");
	}
}

bool Rectangle::isIntersecting(const Rectangle& rectangle) const
{
    return isIntersecting(rectangle.vector.x, rectangle.vector.y, rectangle.width, rectangle.height);
}

bool Rectangle::isIntersecting(double _x, double _y, int _w, int _h) const
{
    int _x_ = vector.x;
    int _y_ = vector.y;
    int _w_ = width;
    int _h_ = height;

    _x_ -= _x;
    _y_ -= _y;

    if(_x_ < 0)
    {
        _w_ += _x_;
        _x_ = 0;
    }
    else if(_x_ + _w_ > _w)
    {
        _w_ = _w - _x_;
    }

    if(_y_ < 0)
    {
        _h_ += _y_;
        _y_ = 0;
    }
    else if(_y_ + _h_ > _h)
    {
        _h_ = _h - _y_;
    }

    if(_w_ <= 0 || _h_ <= 0)
    {
        return false;
    }

    return true;
}

bool Rectangle::isVectorInRect(const int _x, const int _y) const
{
    return (_x >= vector.x) && (_y >= vector.y) && (_x < vector.x + width) && (_y < vector.y + height);
}

bool Rectangle::isVectorInRect(const Vector& p) const
{
    return isVectorInRect(p.x, p.y);
}

ostream& operator<<(ostream& os, const Rectangle& rect)
{
    os << "[" << rect.vector.x << "," << rect.vector.y << " - " << rect.width << "," << rect.height << "]";
    return os;
}

const Rectangle NULL_RECTANGLE(0, 0, 0, 0);
