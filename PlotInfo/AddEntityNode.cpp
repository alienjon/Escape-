/*
 * AddEntityNode.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: the-saint
 */
#include "AddEntityNode.hpp"

#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::string;

AddEntityNode::AddEntityNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& add) : PlotNode(keyword, activation, deactivation),
	mAdd(add)
{
}

void AddEntityNode::activate()
{
	// Get the object type.
	string::size_type pos = 0;
	string type = extractDataLine(mAdd, pos, CHAR_DELIMITER);

	// Get the data.
	string data = mAdd.substr(pos);

	// Add the correct type of entity.
	if(type == "CREATURE")
	{
		pushEvent(EVENT_CREATURE_ADD, data);
	}
	else if(type == "OBJECT")
	{
		pushEvent(EVENT_OBJECT_ADD, data);
	}
	else if(type == "FLASHLIGHT")
	{
		pushEvent(EVENT_FLASHLIGHT_ADD, data);
	}
	else
	{
		Logger::warn("Entity of type '" + type + "' doesn't exist.");
	}

	// Performed and activated.
	mIsPerformed = mIsActivated = true;
	mDistributePlotEvent();
}
