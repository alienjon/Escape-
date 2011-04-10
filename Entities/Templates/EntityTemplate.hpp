/*
 * EntityTemplate.hpp
 *
 *  Created on: Jul 8, 2010
 *      Author: the-saint
 */

#ifndef ENTITYTEMPLATE_HPP_
#define ENTITYTEMPLATE_HPP_

#include <string>

#include "../../Math/Rectangle.hpp"

struct EntityTemplate
{
	/**
	 * @brief Default constructor.
	 * @param _keyword The template's keyword.
	 * @param _anim The template's animation keyword.
	 * @param area The collision area.
	 */
	EntityTemplate(const std::string& _keyword, const std::string& _anim, const Rectangle& area) : keyword(_keyword), animation(_anim), collisionArea(area)
	{}

	/**
	 * The keyword.
	 */
	const std::string keyword;

	/**
	 * This is the animation keyword.  It means different things based on what is being loaded.
	 * For creatures this is the prefix for the animation files.
	 * For objects, it is the single animation that is used for initial display.
	 */
	std::string animation;

	/**
	 * The collision area.
	 */
	Rectangle collisionArea;
};

#endif /* ENTITYTEMPLATE_HPP_ */
