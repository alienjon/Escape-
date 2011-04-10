/*
 * EnvironmentNode.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: the-saint
 */
#include "EnvironmentNode.hpp"

#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Managers/PlotManager.hpp"

using std::string;

const string ENVIRONMENT_LIGHTING = "LIGHTING";
const string ENVIRONMENT_ENTITYDISPLAY = "DISPLAY_HEALTH";

EnvironmentNode::EnvironmentNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& data) : PlotNode(keyword, activation, deactivation),
	mPreviousLightingState(true)
{
	// Get the element and it's data.
	string::size_type pos = 0;
	mElement = extractDataLine(data, pos, CHAR_DELIMITER);
	mElementData = data.substr(pos);
}

void EnvironmentNode::activate()
{
	// Begin by getting the previous lighting state.
	mPreviousLightingState = PlotManager::mDistributeLightingStateRequest();

	string::size_type pos = 0;
	if(mElement == ENVIRONMENT_LIGHTING)
	{
		// The data should say if the lights are to be turned on, turned off, or toggled from one to the other.
		string status = extractDataLine(mElementData, pos, CHAR_DELIMITER);
		if(status == "ON")
		{
			PlotManager::mDistributeSetLightingStateRequest(true); // @todo can this be removed in favor of an Event? (pushEvent())
		}
		else if(status == "OFF")
		{
			PlotManager::mDistributeSetLightingStateRequest(false);
		}
		else if(status == "TOGGLE")
		{
			PlotManager::mDistributeSetLightingStateRequest(!mPreviousLightingState);
		}
		else
		{
			Logger::log("'" + status + "' is an invalid status for a lighting state request.  Ignoring.");
			mIsPerformed = true;
			mDistributePlotEvent();
		}
	}
	else if(mElement == ENVIRONMENT_ENTITYDISPLAY)
	{
		// Push an event based on if a display is being turned on or off.
		string status = extractDataLine(mElementData, pos, CHAR_DELIMITER);
		string creature=extractDataLine(mElementData, pos, CHAR_DELIMITER);
		if(status == "ADD")
		{
			pushEvent(EVENT_ENTITYDISPLAY_ADD, creature);
		}
		else if(status == "REMOVE")
		{
			pushEvent(EVENT_ENTITYDISPLAY_REMOVE, creature);
		}
		else
		{
			Logger::log("'" + status + "' is an invalid status request for a creature display.  Ignoring.");
			mIsPerformed = true;
			mDistributePlotEvent();
		}
	}
	else
	{
		Logger::log("'" + mElement + "' is an invalid environmental element.");
		mIsPerformed = true;
		mDistributePlotEvent();
	}

	// If the deactivation keyword is the same as this node's keyword, then do not deactivate this node.
	if(mKeyword == mDeactivationKeyword)
	{
		mIsPerformed = true;
		mDistributePlotEvent();
	}
}

void EnvironmentNode::deactivate()
{
	// If a deactivation keyword was provided then, upon deactivation, return the lighting state to the state prior to this plot device.
	if(!mDeactivationKeyword.empty())
	{
		PlotManager::mDistributeSetLightingStateRequest(mPreviousLightingState);
		mIsPerformed = true;
	}
}
