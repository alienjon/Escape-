/*
 * WalkToNode.hpp
 *
 *  Created on: Aug 5, 2010
 *      Author: the-saint
 */
#ifndef WALKTONODE_HPP_
#define WALKTONODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"
#include "../Math/Vector.hpp"

class Creature;

/**
 * @brife A walkto node tells a specified creature to walk to a specified point.
 *
 * @note The game screen does the actual telling, but if the creature doesn't exist
 * 		 (or the keyword provided is of a different type) then a warning will be produced.
 */
class WalkToNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The node's keyword.
	 * @param activate The activation keywords.
	 * @param deactivate The deactivation keywords.
	 * @param name The name of the creature to move.
	 * @param point The location for the creature to move towards.
	 */
	WalkToNode(const std::string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivate, const std::string& name, const Vector& point);
	virtual ~WalkToNode();

	/**
	 * @brief Activate the node by telling the creature to move to the point.
	 */
	virtual void activate();

	/**
	 * @brief Listen for when a creature has moved.
	 * @param creature The creature that moved.
	 */
	void creatureMoved(Creature& creature);

	private:
	/**
	 * The name of the creature to move.
	 */
	std::string mName;

	/**
	 * The point the creature is to move towards.
	 */
	Vector mPoint;

	/**
	 * The creature handle (exists once the movement event has been accepted)
	 */
	Creature* mCreature;
};

#endif /* WALKTONODE_HPP_ */
