/*
 * PickupListener.hpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#ifndef PICKUPLISTENER_HPP_
#define PICKUPLISTENER_HPP_

class Item;

/**
 * @brief An interface for objects that are picked up.
 */
class PickupListener
{
	public:
	virtual ~PickupListener() {}

	/**
	 * @brief An item was picked up.
	 * @param item The item picked up.
	 * @return True if the item was successfully picked up.
	 */
	virtual bool itemPickedUp(Item& item) = 0;
};

#endif /* PICKUPLISTENER_HPP_ */
