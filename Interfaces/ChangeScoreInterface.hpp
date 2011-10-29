/*
 * ChangeScoreInterface.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef CHANGESCOREINTERFACE_HPP_
#define CHANGESCOREINTERFACE_HPP_

#include <list>

#include "../Listeners/ChangeScoreListener.hpp"

class ChangeScoreInterface
{
	public:
	/**
	 * @brief Add a change score listener.
	 * @param listener The listener.
	 */
	void addChangeScoreListener(ChangeScoreListener* listener)
	{
		mChangeScoreListeners.push_back(listener);
	}

	/**
	 * @brief Distribute a change score request.
	 * @param score The score to add/subtract.
	 */
	void distributeChangeScore(int score)
	{
		for(std::list<ChangeScoreListener*>::const_iterator it = mChangeScoreListeners.begin(); it != mChangeScoreListeners.end(); ++it)
			(*it)->changeScore(score);
	}

	/**
	 * @brief Remove a change score listener.
	 * @param listener The listener to remove.
	 */
	void removeChangeScoreListener(ChangeScoreListener* listener)
	{
		mChangeScoreListeners.remove(listener);
	}

	private:
	// The list of change score listeners.
	std::list<ChangeScoreListener*> mChangeScoreListeners;
};


#endif /* CHANGESCOREINTERFACE_HPP_ */
