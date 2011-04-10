/*
 * MessageNode.hpp
 *
 *  Created on: Jul 19, 2010
 *      Author: the-saint
 */
#ifndef MESSAGENODE_HPP_
#define MESSAGENODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

class MessageNode : public PlotNode
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
	MessageNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& title, const std::string& message);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * The title of the task.
	 */
	std::string mTitle;

	/**
	 * The detailed message.
	 */
	std::string mMessage;
};

#endif /* MESSAGENODE_HPP_ */
