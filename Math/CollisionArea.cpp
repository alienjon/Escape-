/*
 * CollisionArea.cpp
 *
 *  Created on: Oct 20, 2011
 *      Author: alienjon
 */
#include "CollisionArea.hpp"

using std::list;

void CollisionArea::addRectangle(const Rectangle& rect)
{
	mAreas.push_back(rect);
}

void CollisionArea::addX(int x)
{
	for(list<Rectangle>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
		it->vector.x += x;
}

void CollisionArea::addY(int y)
{
	for(list<Rectangle>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
		it->vector.y += y;
}

void CollisionArea::draw(Renderer& renderer)
{
	for(list<Rectangle>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
		renderer.fillRectangle(*it);
}

bool CollisionArea::isIntersecting(const Rectangle& rect) const
{
	for(list<Rectangle>::const_iterator it = mAreas.begin(); it != mAreas.end(); it++)
		if(it->isIntersecting(rect))
			return true;
	return false;
}
