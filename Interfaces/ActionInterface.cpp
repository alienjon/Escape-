/*
 * ActionInterface.cpp
 *
 *  Created on: Jul 13, 2010
 *      Author: the-saint
 */
#include "ActionInterface.hpp"

void ActionInterface::addAction(Action* action)
{
	mActions.push_back(action);
}

void ActionInterface::clearActions()
{
	// Delete actions.
	for(ActionList::iterator it = mActions.begin(); it != mActions.end(); ++it)
	{
		delete *it;
	}

	mActions.clear();
}

bool ActionInterface::isPerforming() const
{
	return !mActions.empty();
}

void ActionInterface::logic(EnvironmentData& eData)
{
	// Check for actions: If there is a current action set then activate it.
	if(!mActions.empty())
	{
		Action* temp = *(mActions.begin());
		temp->activate(eData);

		// If that action is now performed, then remove it.
		if(temp->isPerformed())
		{
			mActions.pop_front();
			delete temp;
		}
	}
}
