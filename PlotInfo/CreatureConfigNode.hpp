/*
 * CreatureConfigNode.hpp
 *
 *  Created on: Aug 12, 2010
 *      Author: the-saint
 */
#ifndef CREATURECONFIGNODE_HPP_
#define CREATURECONFIGNODE_HPP_

#include <string>

#include "PlotNode.hpp"

/**
 * @brief This is a node that can be used to configure various aspects of creatures (including the player).
 *
 * @note This node is performed upon activation.
 */
class CreatureConfigNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param data The data needed to configure the creature.
	 *
	 * @note The data follows in the following format:
	 * {creature name}:{status to change}:{status data}
	 *
	 * The status to change can be one of the following:
	 * SET_WANDER - This will cause the creature to wander around aimlessly.  No parameters required.
	 * SET_STOP - This will cause the creature to stop wandering.  No parameters required.
	 * SET_SEARCHAREA - This will change the search area of the creature.  Pass the parameters {search span}:{search distance}
	 * SET_FACEDIRECTION - This will change the creature's currently facing direction.  Note that if the creature is wandering then this might change immediately.
	 * SET_ALIGNMENT - Sets the alignment of the creature.
	 */
	CreatureConfigNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& data);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * The data.
	 */
	std::string mData;
};

#endif /* CREATURECONFIGNODE_HPP_ */
