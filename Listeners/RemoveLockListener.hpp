/*
 * RemoveLockListener.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef REMOVELOCKLISTENER_HPP_
#define REMOVELOCKLISTENER_HPP_

#include "../guichan.hpp"

class RemoveLockListener
{
	public:
	/**
	 * @brief Remove a lock.
	 * @param color The color of the lock to remove.
	 */
	virtual void removeLock(gcn::Color color) = 0;
};

#endif /* REMOVELOCKLISTENER_HPP_ */
