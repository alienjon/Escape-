/*
 * PauseGameNode.hpp
 *
 *  Created on: Jun 26, 2010
 *      Author: the-saint
 */
#ifndef PAUSEGAMENODE_HPP_
#define PAUSEGAMENODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A plot node which will pause the game itself.
 *
 * @note This node will not give pause to other nodes, just the game (if you want pauses between events
 * then @see PauseNode
 */
class PauseGameNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword This node's keyword.
	 * @param activate The activation keywords.
	 * @param deactivate The deactivation keywords.
	 * @param duration The duration to pause the game (or == 0 to pause indefinitely)
	 */
	PauseGameNode(const std::string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, unsigned int duration);

	/**
	 * @brief Activate the node by pausing gameplay.
	 */
	virtual void activate();

	/**
	 * @brief Deactivate the node by resuming gameplay.
	 */
	virtual void deactivate();

	/**
	 * @brief Perform logic.
	 * @return True if the node has completed performing.
	 */
	virtual bool logic();

	private:
	/**
	 * The timer.
	 */
	Timer mTimer;

	/**
	 * The duration of the timer.
	 */
	unsigned int mDuration;
};

#endif /* PAUSEGAMENODE_HPP_ */
