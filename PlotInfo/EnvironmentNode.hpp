/*
 * EnvironmentNode.hpp
 *
 *  Created on: Jun 25, 2010
 *      Author: the-saint
 */
#ifndef ENVIRONMENTNODE_HPP_
#define ENVIRONMENTNODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

class EnvironmentNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param This node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param data Information for what change to the environment is to be made.
	 */
	EnvironmentNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& data);

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
	 * The environmental element this node is changing.
	 */
	std::string mElement;

	/**
	 * This is the data itself for the element to use.
	 */
	std::string mElementData;

	/**
	 * The lighting state before the node was called into action.
	 */
	bool mPreviousLightingState;
};

#endif /* ENVIRONMENTNODE_HPP_ */
