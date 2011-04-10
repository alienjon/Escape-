/*
 * Flashlight.hpp
 *
 *  Created on: Aug 6, 2010
 *      Author: the-saint
 */
#ifndef FLASHLIGHT_HPP_
#define FLASHLIGHT_HPP_

#include <string>

#include "../../Entities/Templates/EntityTemplate.hpp"
#include "../../Entities/Non-Creatures/Item.hpp"

class Creature;
class EnvironmentData;

/**
 * @brief A flashlight shines light when is is being held.  They can possess a number of parameters.
 */
class Flashlight : public Item
{
	public:
	/**
	 * @brief Default constructor.
	 * @param name The name of the flashlight.
	 * @param tmpl The animation template this light displays while on the map.
	 * @param distance The distance the light shines.
	 * @param span The span the light will shine at its distance.
	 */
	Flashlight(const std::string& name, const EntityTemplate& tmpl, unsigned int distance, unsigned int span);

	/**
	 * @brief While the flashlight is held it shines a light in a provided direction.
	 * @param eData The environment data.
	 * @param holder The creature holding the item.
	 */
	virtual void heldLogic(EnvironmentData& eData, Creature& holder);

	private:
	/**
	 * The distance and span.
	 */
	unsigned int mDistance,
				 mSpan;
};

#endif /* FLASHLIGHT_HPP_ */
