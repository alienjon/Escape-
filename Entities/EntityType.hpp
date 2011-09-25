/*
 * EntityType.hpp
 *
 *  Created on: May 17, 2010
 *      Author: the-saint
 */

#ifndef ENTITYTYPE_HPP_
#define ENTITYTYPE_HPP_

#include <string>

typedef enum
{
	ENTITY_CREATURE,
	ENTITY_PLAYER,
	ENTITY_NONDISPLAYING,
	ENTITY_EXPLOSION,
	ENTITY_OBJECT,
	ENTITY_ITEM,
	ENTITY_NULL
} EntityType;

/**
 * @brief Determine the type of being in character representation.
 * @param type The type of being.
 * @return The string representation of the being type.
 */
std::string getEntityType(EntityType type);

/**
 * @brief Determine the type of entity representation by it's string representation.
 * @param type The string representation of the type.
 * @return The entity type.
 */
EntityType getEntityType(const std::string& type);

#endif /* ENTITYTYPE_HPP_ */
