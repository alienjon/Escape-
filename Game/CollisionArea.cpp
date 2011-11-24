/*
 * CollisionArea.cpp
 *
 *  Created on: Oct 20, 2011
 *      Author: alienjon
 */
#include "CollisionArea.hpp"

#include "../Game/Math.hpp"

using std::list;

void CollisionArea::add(const sf::Shape& rect)
{
	mAreas.push_back(rect);
}

void CollisionArea::setPosition(float x, float y)
{
	for(list<sf::Shape>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
		for(unsigned int i = 0; i != it->GetPointsCount(); ++i)
			it->SetPosition(x, y);
}

void CollisionArea::draw(sf::RenderWindow& renderer)
{
	for(list<sf::Shape>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
		renderer.Draw(*it);
}

bool CollisionArea::isIntersecting(const sf::Shape& area) const
{
	for(list<sf::Shape>::const_iterator it = mAreas.begin(); it != mAreas.end(); it++)
		if(isPolyIntersecting(area, *it))
			return true;
	return false;
}
