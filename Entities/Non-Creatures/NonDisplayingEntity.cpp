/*
 * NonDisplayingEntity.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */

#include "NonDisplayingEntity.hpp"

#include <stdexcept>
#include <string>

#include "../../Game/EnvironmentData.hpp"
#include "../../Game/Game.hpp"
#include "../../Engine/Colors.hpp"
#include "../../main.hpp"

using std::string;

// @note The provided area describes the initial position of the entity as the x,y position and the collision area as the widthxheight.
//		 The collision area offset (the collision area's x,y) is zero because the entire nondisplayingentity is collidable, potentially.
NonDisplayingEntity::NonDisplayingEntity(const string& name, const Rectangle& area) : Entity(name, 0, 0, Rectangle(0, 0, area.width, area.height))
{
    mType = ENTITY_NONDISPLAYING;
    setPosition(area.vector.x, area.vector.y);
}

//NonDisplayingEntity::NonDisplayingEntity(const string& data)
//{
//    // Decode the data string.
//    string::size_type pos = 0;
//
//    /*
//     * Load this entity in the following manner:
//     * 1) Entity id
//     * 2) Dimension
//     * @note The type isn't loaded, as it should be used by whatever is creating the entity.
//     */
//    mId = (unsigned int)toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    setX(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    setY(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    mCollisionArea.width = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mCollisionArea.height = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//}

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

string NonDisplayingEntity::extract() const
{return ""; // @todo need to implement saving entities.
//    // Store the value's, with a delimiter between each value, and then return the encoded value.
//    return toString(getId()) + CHAR_DELIMITER + toString(getX()) + CHAR_DELIMITER + toString(getY()) +
//           CHAR_DELIMITER + toString(getWidth()) + CHAR_DELIMITER + toString(getHeight());
}

void NonDisplayingEntity::logic(EnvironmentData& eData)
{
    // Check for actions: If there is a current action set then activate it but don't do anything else.
    ActionInterface::logic(eData);
}
