/*
 * LevelData.hpp
 *
 *  Created on: Jun 3, 2010
 *      Author: the-saint
 */

#ifndef LEVELDATA_HPP_
#define LEVELDATA_HPP_

#include <list>
#include <map>
#include <string>

#include "../Entities/Alignment.hpp"
#include "../LevelInfo/ElipData.hpp"
#include "../Math/Ellipse.hpp"
#include "../Entities/EntityData.hpp"
#include "../LevelInfo/QuadData.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../LevelInfo/RectData.hpp"
#include "../LevelInfo/PortalData.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief The level data is the collection of information needed to load a predefined level.
 */
struct LevelData
{
	/**
	 * @brief Method to add an area for ease of use.
	 * @param name The name of the area.
	 * @param area The physical area.
	 */
	void addArea(const std::string& name, const Rectangle& area)
	{
		area_data.push_back(RectData(name, area));
	}

	/**
	 * @brief Method to add an entity for ease of use.
	 * @param entity The entity to add.
	 */
	void addEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	/**
	 * @brief Method to add a light for ease of use.
	 * @param name The name of the light.
	 * @param area The physical area.
	 */
	void addLightQuad(const std::string& name, const Quadrilateral& area)
	{
		light_quad_data.push_back(QuadData(name, area));
	}

	/**
	 * @brief Method to add a light for ease of use.
	 * @param name The name of the light.
	 * @param area The physical area.
	 */
	void addLightElip(const std::string& name, const Ellipse& area)
	{
		light_elip_data.push_back(ElipData(name, area));
	}

	/**
	 * @brief Method to add a portal for ease of use.
	 * @param portalA The entry area's id.
	 * @param portalBMap The map name the second area is in.
	 * @param portalB The exit area's id.
	 */
	void addPortal(const std::string& portalA, const std::string& portalBMap, const std::string& portalB)
	{
		portal_data.push_back(PortalData(portalA, portalBMap, portalB));
	}

	/**
	 * The level's name.
	 */
	std::string name;

	/**
	 * This is the entering position of the entities into the level.
	 * The key is the entry's ID (the unsigned int).  The point is the position.
	 */
	std::map<unsigned int, Vector> entry_points;

	/**
	 * The list of areas.
	 */
	std::list<RectData> area_data;

	/**
	 * The list of objects and creatures.
	 */
	std::list<EntityData> object_data;
	std::list<EntityData> creature_data;

	/**
	 * The lights.
	 */
	std::list<QuadData> light_quad_data;
	std::list<ElipData> light_elip_data;

	/**
	 * The list of portals.
	 */
	std::list<PortalData> portal_data;

	/**
	 * The map data.
	 */
	std::string mapData;

	/**
	 * The entities who will reside in the level.
	 */
	std::list<Entity*> entities;
};

#endif /* LEVELDATA_HPP_ */
