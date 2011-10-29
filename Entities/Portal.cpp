/*
 * Portal.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#include "Portal.hpp"

#include "../Math/Rectangle.hpp"

Portal::Portal()
{
	mSetSize(40, 40);
	setCollidable(false);
}

void Portal::collide(Entity& entity)
{
	// If the player collides with the portal and all the locks are removed, end the level.
	if(mLocks.empty() && entity.getType() == ENTITY_PLAYER)
	{
		distributeLevelComplete();
	}
}

void Portal::draw(Renderer& renderer)
{
	//@todo how do I want to display the renderer?
	Rectangle area = getDimension();
	renderer.setColor(gcn::Color(0, 0, 255));
	renderer.fillRectangle(area);
	renderer.setColor(gcn::Color(0, 0, 0));
	area.vector.x = area.vector.x + 5;
	area.vector.y = area.vector.y + 5;
	area.width = area.width - 10;
	area.height= area.height- 10;
	renderer.fillRectangle(area);
}
