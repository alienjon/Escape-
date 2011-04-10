/*
 * HoldInputNode.hpp
 *
 *  Created on: Aug 5, 2010
 *      Author: the-saint
 */
#ifndef HOLDINPUTNODE_HPP_
#define HOLDINPUTNODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

/**
 * @brief This node holds all input until the deactivation is called.
 */
class HoldInputNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The keyword for this node.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 */
	HoldInputNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	/**
	 * @brief Deactivate the node.
	 */
	virtual void deactivate();
};

#endif /* HOLDINPUTNODE_HPP_ */
