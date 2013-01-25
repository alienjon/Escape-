/*
 * CollisionArea.cpp
 *
 *  Created on: Oct 20, 2011
 *      Author: alienjon
 */
#include "CollisionArea.hpp"

#include "../Game/Math.hpp"

using std::list;

void CollisionArea::add(const sf::FloatRect& rect)
{
	mAreas.push_back(rect);
}

void CollisionArea::setPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void CollisionArea::draw(sf::RenderWindow& renderer)
{
	for(list<sf::FloatRect>::iterator it = mAreas.begin(); it != mAreas.end(); it++)
	{
		sf::RectangleShape rect(sf::Vector2f(it->width, it->height));
		rect.setPosition(it->left + mPosition.x, it->top + mPosition.y);
		renderer.draw(rect);
	}
}

bool CollisionArea::isIntersecting(const sf::FloatRect& area) const
{
	sf::FloatRect new_area = area;//@todo make sure this code works (originally this was shapes that held their own coordinates, now there's a single offset coordinate)
	new_area.left -= mPosition.x;
	new_area.top -= mPosition.y;

	for(list<sf::FloatRect>::const_iterator it = mAreas.begin(); it != mAreas.end(); it++)
		if(new_area.intersects(*it))
			return true;
	return false;
}
