/*
 * AddLockListener.hpp
 *
 *  Created on: Nov 1, 2011
 *      Author: alienjon
 */
#ifndef ADDLOCKLISTENER_HPP_
#define ADDLOCKLISTENER_HPP_

#include "../guichan.hpp"

class AddLockListener
{
	public:
	/**
	 * @brief Add a lock.
	 * @param color The lock color to add.
	 */
	virtual void addLock(gcn::Color color) = 0;
};

#endif /* ADDLOCKLISTENER_HPP_ */
