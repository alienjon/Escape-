/*
 * RemoveLockInterface.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef REMOVELOCKINTERFACE_HPP_
#define REMOVELOCKINTERFACE_HPP_

#include <list>
#include <SFML/Graphics.hpp>

#include "../Listeners/RemoveLockListener.hpp"

class RemoveLockInterface
{
	public:
	/**
	 * @brief Add a remove lock listener.
	 * @param listener The listener to add.
	 */
	void addRemoveLockListener(RemoveLockListener* listener)
	{
		mRemoveLockListeners.push_back(listener);
	}

	/**
	 * @brief Tell all remove lock listeners to remove a lock.
	 * @param color The color of the lock to remove.
	 */
	void distributeRemoveLock(sf::Color color)
	{
		for(std::list<RemoveLockListener*>::iterator it = mRemoveLockListeners.begin(); it != mRemoveLockListeners.end(); it++)
			(*it)->removeLock(color);
	}

	/**
	 * @brief Remove a remove lock listener.
	 * @param listener The listener to remove.
	 */
	void removeRemoveLockListener(RemoveLockListener* listener)
	{
		mRemoveLockListeners.remove(listener);
	}

	private:
	// The list of remove lock listeners.
	std::list<RemoveLockListener*> mRemoveLockListeners;
};

#endif /* REMOVELOCKINTERFACE_HPP_ */
