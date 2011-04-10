/*
 * TaskNode.hpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */
#ifndef TASKNODE_HPP_
#define TASKNODE_HPP_

#include <string>

#include "PlotNode.hpp"

/**
 * @brief Display a simple, disappearing message to the user.
 */
class TaskNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword This node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param title The title of the task.
	 * @param message The detailed explanation of the task.
	 */
	TaskNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& title, const std::string& message);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	/**
	 * @brief Deactivate the node.
	 */
	virtual void deactivate();

	private:
	/**
	 * The title of the task.
	 */
	std::string mTitle;

	/**
	 * The detailed message.
	 */
	std::string mMessage;

	/**
	 * The task's ID.
	 */
	unsigned int mId;
};

#endif /* TASKNODE_HPP_ */
