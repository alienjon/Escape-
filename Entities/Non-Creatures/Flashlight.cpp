/*
 * Flashlight.cpp
 *
 *  Created on: Aug 6, 2010
 *      Author: the-saint
 */
#include "Flashlight.hpp"

#include "../../Entities/Creatures/Creature.hpp"
#include "../../Math/Rectangle.hpp"

using std::string;

Flashlight::Flashlight(const string& name, const EntityTemplate& tmpl, unsigned int distance, unsigned int span) : Item(name, tmpl),
	mDistance(distance),
	mSpan(span)
{
}

//void Flashlight::heldLogic(EnvironmentData& eData, Creature& holder)//@todo review
//{
//	// Add a light around the player.
//	const Rectangle& spriteDim = holder.getVisibleArea();
//	const Vector p = spriteDim.getCenter();
//	eData.addLight(Ellipse(p.x - eData.getXOffset(), p.y - eData.getYOffset(), spriteDim.width / 3, spriteDim.height / 3));
//
//	// And the flashlight light.
//	Vector offset_point(eData.getXOffset(), eData.getYOffset());
//	eData.addLight(getIsoscelesTrapezoid(holder.getVisibleArea().getCenter() - offset_point, holder.getFacingVector() - offset_point, mDistance, (getWidth() + getHeight()) / 2, mSpan));
//}
