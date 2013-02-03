/*
 * SurprisePickup.hpp
 *
 *  Created on: Feb 2, 2013
 *      Author: alienjon
 */
#ifndef SURPRISEPICKUP_HPP_
#define SURPRISEPICKUP_HPP_

#include "../Entities/Entity.hpp"

class Level;

/*
 * @brief A pickup whose effects are unknown.
 */
class SurprisePickup : public Entity
{
	public:
	/**
	 * @brief Default constructor.
	 * @param level The level in which the pickup exists.
	 */
	SurprisePickup(Level& level);
	virtual ~SurprisePickup();

	/**
	 * @brief The surprise pickup collided with an entity.
	 * @param entity The entity collided with.
	 */
	virtual void collide(Entity& entity);

	private:
	// The level in which the pickup exists.
	Level& mLevel;
};

#endif /* TELEPORTER_HPP_ */
