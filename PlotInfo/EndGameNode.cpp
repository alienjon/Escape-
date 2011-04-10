/*
 * EndGameNode.cpp
 *
 *  Created on: Aug 19, 2010
 *      Author: the-saint
 */
#include "EndGameNode.hpp"

using std::string;

EndGameNode::EndGameNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& images) : PlotNode(keyword, activation, deactivation),
	mImages(images)
{
}

void EndGameNode::activate()
{
	pushEvent(EVENT_MAINMENU, mImages);
	mDistributePlotEvent();
	mIsPerformed = true;
}
