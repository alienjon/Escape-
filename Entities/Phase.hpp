/*
 * Phase.hpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#ifndef PHASE_HPP_
#define PHASE_HPP_

#include "../Entities/Item.hpp"

/**
 * @brief A phase is an item that allows the player to move in a specified direction by one cell.
 */
class Phase : public Item
{
	public:
	/**
	 * @brief Default constructor.
	 */
	Phase();

	/**
	 * @brief Get the filename of the item's image.
	 * @return The filename of the item's image.
	 */
	virtual const std::string& getImageFilename() const;

	private:
	/**
	 * @brief Perform the item's specific action.
	 * @note This is to be overwritten but child classes so that the actual effects occur when 'use()' is called.
	 */
	virtual void mPerform();
};

#endif /* PHASE_HPP_ */
