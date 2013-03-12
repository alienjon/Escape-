/*
 * KeyPickedUpListener.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef KEYPICKEDUPLISTENER_HPP_
#define KEYPICKEDUPLISTENER_HPP_

class KeyPickedUpListener
{
	public:
	virtual ~KeyPickedUpListener() {}

	/**
	 * @brief The level's key was picked up.
	 */
	virtual void keyPickedUp() = 0;
};

#endif /* KEYPICKEDUPLISTENER_HPP_ */
