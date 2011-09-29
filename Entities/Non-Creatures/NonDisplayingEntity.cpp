/*
 * NonDisplayingEntity.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */

#include "NonDisplayingEntity.hpp"

#include <stdexcept>
#include <string>

#include "../../Game/Game.hpp"
#include "../../Engine/Colors.hpp"
#include "../../main.hpp"

using std::string;

// @note The provided area describes the initial position of the entity as the x,y position and the collision area as the widthxheight.
//		 The collision area offset (the collision area's x,y) is zero because the entire nondisplayingentity is collidable, potentially.
NonDisplayingEntity::NonDisplayingEntity(const string& name, const Rectangle& area) : Entity(name, 0, Rectangle(0, 0, area.width, area.height))
{
    mType = ENTITY_NONDISPLAYING;
    setPosition(area.vector.x, area.vector.y);
}

void NonDisplayingEntity::damage(unsigned int damage)
{
	// Non-displaying entities are not damaged.
}

void NonDisplayingEntity::draw(Renderer& renderer)
{
    // If we're debugging, draw the collision area.
    if(Game::isDebug())
    {
        // Set the collision color.
        renderer.setColor(COLOR_RED);
        renderer.fillRectangle(gcn::Rectangle(getX(), getY(), getWidth(), getHeight()));
    }
}

//void NonDisplayingEntity::logic(EnvironmentData& eData)//@todo review
//{
//    // Check for actions: If there is a current action set then activate it but don't do anything else.
//    ActionInterface::logic(eData);
//}
