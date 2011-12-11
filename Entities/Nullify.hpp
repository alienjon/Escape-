/*
 * Nullify.hpp
 *
 *  Created on: Dec 10, 2011
 *      Author: alienjon
 */
#ifndef NULLIFY_HPP_
#define NULLIFY_HPP_

#include <string>

#include "../Entities/Item.hpp"

class Level;

/**
 * @brief A nullify
 */
class Nullify : public Item
{
	public:
	/**
	 * @brief Default constructor.
	 * @param level The level in which the item exists.
	 */
	Nullify(Level& level);

	/**
	 * @brief Get the image filename for the nullify icon.
	 * @return The filename of the nullify icon.
	 */
	virtual const std::string& getImageFilename() const;

	protected:
	/**
	 * @brief Nullify all effects currently in play.
	 * @param creature The creature calling the nullify.
	 */
	virtual void mPerform(Creature& creature);

	private:
	// The level in which the item exists.
	Level& mLevel;
};

#endif /* NULLIFY_HPP_ */
