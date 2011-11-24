/*
 * ActionInterface.hpp
 *
 *  Created on: Aug 31, 2009
 *      Author: alienjon
 */
#ifndef ACTIONINTERFACE_HPP_
#define ACTIONINTERFACE_HPP_

#include "../Actions/Action.hpp"

class Level;

/**
 * @brief The action interface allows a class to extend itself to accept actions.
 *
 * The interface provides both a means to add, remove and perform actions in a
 * queued order.  Memory management must be handled independently of this interface,
 * however, as the destructor for this interface won't be called until the extended
 * class has already been destroyed (so any referred objects will be deleted).  This
 * probably just needs a call to 'destroyActions() in the extending class, however.
 */
class ActionInterface
{
    public:
    virtual ~ActionInterface()
    {}

    /**
     * @brief Add an action for this sprite to perform.
     * @param action The action to add to the queue.
     */
    inline void addAction(Action* action)
    {
    	mActions.push_back(action);
    }

    /**
     * @brief Clear the current actions.
     */
    inline void clearActions()
    {
    	// Delete actions.
    	for(ActionList::iterator it = mActions.begin(); it != mActions.end(); ++it)
    	{
    		delete *it;
    	}

    	mActions.clear();
    }

    /**
     * @brief The performing state.
     * @return True if there is currently an active action.
     */
    inline bool isPerforming() const
    {
    	return !mActions.empty();
    }

    /**
     * @brief Perform logic.
     * @param level The level in which the action takes place.
     */
    inline void logic(Level& level)
    {
    	// Check for actions: If there is a current action set then activate it.
    	if(!mActions.empty())
    	{
    		Action* temp = *(mActions.begin());
    		temp->activate(level);

    		// If that action is now performed, then remove it.
    		if(temp->isPerformed())
    		{
    			mActions.pop_front();
    			delete temp;
    		}
    	}
    }

    private:
    // This is the action queue for this being.
    ActionList mActions;
};

#endif /* ACTIONINTERFACE_HPP_ */
