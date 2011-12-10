/*
 * MultipleActionsAction.cpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */
#include "MultipleActionsAction.hpp"

MultipleActionsAction::MultipleActionsAction(ActionList* actions) : mActions(actions)
{
}

MultipleActionsAction::~MultipleActionsAction()
{
	// Delete the action list.
	if(mActions)
	{
		for(ActionList::iterator it = mActions->begin(); it != mActions->end(); ++it)
			delete *it;
		delete mActions;
	}
}

void MultipleActionsAction::activate(Level& level)
{
    // Go through the actions list and activate all of the remaining actions.
    for(ActionList::iterator it = mActions->begin(); it != mActions->end(); ++it)
    	(*it)->activate(level);

    // For each item in the list, if that item has been performed, add it to a list to be removed.
    ActionList removalList;
    for(ActionList::iterator it = mActions->begin(); it != mActions->end(); ++it)
    {
        // If the current action has been performed, add it to the list to be removed.
        if((*it)->isPerformed())
        {
            // Add it to the removal list.
            removalList.push_back((*it));

            // Delete the action (it will be removed from the list later).
            delete (*it);
        }
    }

    // Now go through the removal list and remove each item from the actions list.
    for(ActionList::iterator it = removalList.begin(); it != removalList.end(); ++it)
        mActions->remove(*it);

    // Next, if the actions list is empty, then the multiple actions action has been performed.
    if(mActions->empty())
    {
        mPerformed = true;
        return;
    }
}
