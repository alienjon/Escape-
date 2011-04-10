/*
 * PauseNode.hpp
 *
 *  Created on: Jun 24, 2010
 *      Author: the-saint
 */
#ifndef PAUSENODE_HPP_
#define PAUSENODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A plot device that waits a period of time.
 *
 * A timer can be provided an activation keyword (which it will wait to receive before
 * starting the timer) and will deactivate when the timer is up or until the deactivation
 * code is received.
 */
class PauseNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The pause node's keyword.
	 * @param activate The activation keywords.
	 * @param deactivate The deactivation keywords.
	 * @param duration The duration.
	 */
	PauseNode(const std::string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, unsigned int duration);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

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
	 * The duration the timer should count to.
	 */
	unsigned int mDuration;
};

#endif /* PAUSENODE_HPP_ */
