/*
 * Pickup.cpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#include "Pickup.hpp"

Pickup::Pickup(int value, const gcn::Color& color, unsigned int size) :
	mValue(value),
	mColor(color),
	mSize(size)
{
}

void Pickup::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Add to the score.
		distributeChangeScore(mValue);

		// Kill the pickup.
		mDie();
	}
}

void Pickup::draw(Renderer& renderer)
{
	renderer.setColor(mColor);
	renderer.fillEllipse(getX() - (mSize / 2), getY() - (mSize / 2), mSize, mSize);
}
