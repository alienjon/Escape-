/*
 * DebugNode.hpp
 *
 *  Created on: Jun 25, 2010
 *      Author: the-saint
 */
#ifndef DEBUGNODE_HPP_
#define DEBUGNODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

/**
 * @brief A node for debugging the plot system.
 */
class DebugNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param This node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param message An optional debug message.
	 */
	DebugNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& message);

	/**
	 * @brief Perform logic.
	 */
	virtual void activate();

	private:
	/**
	 * A debug message.
	 */
	std::string mMessage;
};

#endif /* DEBUGNODE_HPP_ */
