/*
 * Phase.hpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#ifndef PHASE_HPP_
#define PHASE_HPP_

#include "../Entities/Item.hpp"

class Creature;
class Level;

/**
 * @brief A phase is an item that allows the player to move in a specified direction by one cell.
 */
class Phase : public Item
{
	public:
	/**
	 * @brief Default constructor.
	 * @param level The level in which the phase exists.
	 */
	Phase(Level& level);

	/**
	 * @brief Get the filename of the item's image.
	 * @return The filename of the item's image.
	 */
	virtual const std::string& getImageFilename() const;

	protected:
	/**
	 * @brief Use the item.
	 * @param creature The creature using this item.
	 */
	virtual void mPerform(Creature& creature);

	private:
	// The level in which this phase exists.
	Level& mLevel;
};

#endif /* PHASE_HPP_ */
