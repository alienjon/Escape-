/*
 * ChangeScoreListener.hpp
 *
 *  Created on: Oct 10, 2011
 *      Author: alienjon
 */
#ifndef CHANGESCORELISTENER_HPP_
#define CHANGESCORELISTENER_HPP_

/**
 * @brief This is an interface listener for when scores change.
 */
class ChangeScoreListener
{
	public:
	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change) = 0;
};

#endif /* CHANGESCORELISTENER_HPP_ */
