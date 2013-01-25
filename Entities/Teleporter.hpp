/*
 * Teleporter.hpp
 *
 *  Created on: Dec 1, 2011
 *      Author: alienjon
 */
#ifndef TELEPORTER_HPP_
#define TELEPORTER_HPP_

#include "../Entities/Creature.hpp"
#include "../Listeners/CreatureWaypointListener.hpp"

class Level;

/*
 * @brief A teleporter is a creature that takes up the width or height of one side of the map
 * and slowly moves across to the other side.  When it reaches the other side it dies.  If it
 * hits the player on the way the player is automatically teleported to a random area of the map.
 */
class Teleporter : public Creature, public CreatureWaypointListener//@todo keep?
{
	public:
	/**
	 * @brief Default constructor.
	 * @param width The width of the teleporter.
	 * @param height The height of the teleporter.
	 * @param level The level in which the teleporter exists.
	 */
	Teleporter(unsigned int width, unsigned int height, Level& level);
	virtual ~Teleporter();

	/**
	 * @brief The teleporter collided with an entity.
	 * @param entity The entity collided with.
	 */
	virtual void collide(Entity& entity);

	/**
	 * @brief A creature moved.
	 * @param creature The creature that moved.
	 */
	virtual void creatureMoved(Creature& creature);

	private:
	Level& mLevel;
};

#endif /* TELEPORTER_HPP_ */
