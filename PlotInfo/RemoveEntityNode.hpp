/*
 * RemoveEntityNode.hpp
 *
 *  Created on: Jul 22, 2010
 *      Author: the-saint
 */
#ifndef REMOVEENTITYNODE_HPP_
#define REMOVEENTITYNODE_HPP_

#include <string>

#include "PlotNode.hpp"

/**
 * @brief A remove entity node removes an entity from the current level.
 */
class RemoveEntityNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The keyword for this node.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param remove The keyword of the entity to remove.
	 */
	RemoveEntityNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& remove);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * The keyword of the entity for removal.
	 */
	std::string mRemove;
};

#endif /* REMOVEENTITYNODE_HPP_ */
