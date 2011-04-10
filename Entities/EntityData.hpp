/*
 * EntityData.hpp
 *
 *  Created on: Jun 14, 2010
 *      Author: the-saint
 */

#ifndef ENTITYDATA_HPP_
#define ENTITYDATA_HPP_

#include <string>

#include "../Math/Vector.hpp"

struct EntityData
{
	/**
	 * Default constructor for ease of use.
	 */
	EntityData(const std::string& _name, const std::string& _tmpl, const Vector& pos, unsigned int maxHealth, unsigned int maxDefense, const std::string& _ali = "NEUTRAL") :
																																											name(_name),
																																											tmpl(_tmpl),
																																											position(pos),
																																											max_health(maxHealth),
																																											max_defense(maxDefense),
																																											alignment(_ali)
	{
	}

	/**
	 * The name of the object.
	 */
	std::string name;

	/**
	 * The name of the template this entity will use.
	 */
	std::string tmpl;

	/**
	 * This is the location of the object.
	 */
	Vector position;

	/**
	 * The maximum health and defense of this entity.
	 */
	unsigned int max_health,
				 max_defense;

	/**
	 * The creature's alignment.
	 */
	std::string alignment;
};

#endif /* ENTITYDATA_HPP_ */
