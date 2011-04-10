/*
 * AddEntityNode.hpp
 *
 *  Created on: Jul 22, 2010
 *      Author: the-saint
 */
#ifndef ADDENTITYNODE_HPP_
#define ADDENTITYNODE_HPP_

#include "PlotNode.hpp"

/**
 * @brief Adds an entity to the current level.
 */
class AddEntityNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The keyword for this node.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param add The keyword of the entity to add.
	 */
	AddEntityNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& add);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * The data for the entity to add.
	 */
	std::string mAdd;
};

#endif /* ADDENTITYNODE_HPP_ */
