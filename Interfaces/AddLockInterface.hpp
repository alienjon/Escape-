/*
 * AddLockInterface.hpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#ifndef ADDLOCKINTERFACE_HPP_
#define ADDLOCKINTERFACE_HPP_

#include <list>
#include <SFML/Graphics.hpp>

#include "../Listeners/AddLockListener.hpp"

class AddLockInterface
{
	public:
	/**
	 * @brief Add an AddLockListener.
	 * @param listener The listener to add.
	 */
	inline void addAddLockListener(AddLockListener* listener)
	{
		mAddLockListeners.push_back(listener);
	}

	/**
	 * @brief Distribute an add lock event.
	 * @param color The color of the lock to add.
	 */
	inline void distributeAddLock(sf::Color color)
	{
		for(std::list<AddLockListener*>::iterator it = mAddLockListeners.begin(); it != mAddLockListeners.end(); it++)
			(*it)->addLock(color);
	}

	/**
	 * @brief Remove an AddLockListener.
	 * @param listener The listener to remove.
	 */
	inline void removeAddLockListener(AddLockListener* listener)
	{
		mAddLockListeners.remove(listener);
	}

	private:
	// The list of addlocklisteners.
	std::list<AddLockListener*> mAddLockListeners;
};

#endif /* ADDLOCKINTERFACE_HPP_ */
