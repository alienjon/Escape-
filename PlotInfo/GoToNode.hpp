/*
 * GoToNode.hpp
 *
 *  Created on: Jul 20, 2010
 *      Author: the-saint
 */
#ifndef GOTONODE_HPP_
#define GOTONODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief This node moves a creature to a specified point at a specified level.
 */
class GoToNode : public PlotNode
{
	public:
	/**
	 * @brief The default constructor.
	 * @param keyword This node's keyword.
	 * @param activation The activation keywords.
	 * @param level The name of the level to move the object to.
	 * @param location The location within the level to move the object to.
	 *
	 * @note The deactivation keyword is actually ignored because this node deactivates immediately upon activating.
	 */
	GoToNode(const std::string& keyword, const NodeKeywordSet& activation, const std::string& level, const Vector& location);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * The object name, level and location to move to.
	 */
	std::string mLevel;
	Vector mLocation;
};

#endif /* GOTONODE_HPP_ */
