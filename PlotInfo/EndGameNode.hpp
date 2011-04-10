/*
 * EndGameNode.hpp
 *
 *  Created on: Aug 19, 2010
 *      Author: the-saint
 */
#ifndef ENDGAMENODE_HPP_
#define ENDGAMENODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

/**
 * @brief This node will end the game by showing a series of credit screens followed by returning to the menu screen.
 */
class EndGameNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param This node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param images This is a delimited string of images to display before returning to the main menu.
	 */
	EndGameNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& images);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	private:
	/**
	 * This is a delimited string of images (one for each credit screen).
	 */
	std::string mImages;
};

#endif /* ENDGAMENODE_HPP_ */
