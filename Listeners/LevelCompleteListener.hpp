/*
 * LevelCompleteListener.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef LEVELCOMPLETELISTENER_HPP_
#define LEVELCOMPLETELISTENER_HPP_

class LevelCompleteListener
{
	public:
	virtual ~LevelCompleteListener() {}

	/**
	 * @brief The level is complete.
	 */
	virtual void levelComplete() = 0;
};

#endif /* LEVELCOMPLETELISTENER_HPP_ */
