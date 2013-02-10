/*
 * AddLockListener.hpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#ifndef ADDLOCKLISTENER_HPP_
#define ADDLOCKLISTENER_HPP_

#include <SFML/Graphics.hpp>

class AddLockListener
{
	public:
	virtual ~AddLockListener() {}

	/**
	 * @brief Add a lock.
	 * @param color The lock color to add.
	 */
	virtual void addLock(sf::Color color) = 0;
};

#endif /* ADDLOCKLISTENER_HPP_ */
