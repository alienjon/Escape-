/*
 * Key.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#include "KeyEntity.hpp"

#include "../Game/Level.hpp"

KeyEntity::KeyEntity(gcn::Color color) :
	mColor(color)
{
	mSetSize(20, 20);//@todo how will the KeyEntity's be handled visually?
}

void KeyEntity::collide(Entity& entity)
{
	// If the entity was a player, then add a score to the level and die.
	if(entity.getType() == Entity::ENTITY_PLAYER)
	{
		// Remove the key.
		distributeRemoveLock(mColor);

		// Add to the score.
		distributeChangeScore(50);//@todo how many points should be awarded for obtaining a key?

		// Kill the entity.
		mDie();
	}
}

void KeyEntity::draw(Renderer& renderer)
{
	renderer.setColor(mColor);
	renderer.fillRectangle(Rectangle(getDimension()));
}
