/*
 * EnvironmentInterface.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */
#include "EnvironmentInterface.hpp"

#include "../Engine/Logger.hpp"

using std::list;

bool EnvironmentInterface::mDistributeLightingStateRequest()
{
	// If there aren't any environment request listeners, then inform the user.
	if(mEnvironmentalRequestListeners.empty())
	{
		Logger::log("Request for an environmental lighting state failed.  No listeners added.");
		return true;
	}

	// Return the state of the first environment.
	return mEnvironmentalRequestListeners.front()->getLightingState();
}

void EnvironmentInterface::mDistributeSetLightingStateRequest(bool state)
{
	for(list<EnvironmentRequestListener*>::iterator it = mEnvironmentalRequestListeners.begin(); it != mEnvironmentalRequestListeners.end(); ++it)
	{
		(*it)->setLightingState(state);
	}
}

void EnvironmentInterface::addEnvironmentalRequestListener(EnvironmentRequestListener* listener)
{
	mEnvironmentalRequestListeners.push_back(listener);
}

void EnvironmentInterface::removeEnvironmentalRequestListener(EnvironmentRequestListener* listener)
{
	mEnvironmentalRequestListeners.remove(listener);
}

list<EnvironmentRequestListener*> EnvironmentInterface::mEnvironmentalRequestListeners;
