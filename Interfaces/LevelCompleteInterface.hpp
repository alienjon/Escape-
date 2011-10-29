/*
 * LevelCompleteInterface.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef LEVELCOMPLETEINTERFACE_HPP_
#define LEVELCOMPLETEINTERFACE_HPP_

#include <list>

#include "../Listeners/LevelCompleteListener.hpp"

class LevelCompleteInterface
{
	public:
	/**
	 * @brief Add a level complete listener.
	 * @param listener The listener to add.
	 */
	void addLevelCompleteListener(LevelCompleteListener* listener)
	{
		mLevelCompleteListeners.push_back(listener);
	}

	/**
	 * @brief Distribute a level complete signal.
	 */
	void distributeLevelComplete()
	{
		for(std::list<LevelCompleteListener*>::iterator it = mLevelCompleteListeners.begin(); it != mLevelCompleteListeners.end(); it++)
			(*it)->levelComplete();
	}

	/**
	 * @brief Remove a level complete listener.
	 * @param listener The listener to remove.
	 */
	void removeLevelCompleteListener(LevelCompleteListener* listener)
	{
		mLevelCompleteListeners.remove(listener);
	}

	private:
	// The level complete listener list.
	std::list<LevelCompleteListener*> mLevelCompleteListeners;
};

#endif /* LEVELCOMPLETEINTERFACE_HPP_ */
