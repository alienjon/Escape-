/*
 * ActionInterface.hpp
 *
 *  Created on: Aug 31, 2009
 *      Author: alienjon
 */
#ifndef ACTIONINTERFACE_HPP_
#define ACTIONINTERFACE_HPP_

#include "../Actions/Action.hpp"

class EnvironmentData;

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
    virtual void addAction(Action* action);

    /**
     * @brief Clear the current actions.
     */
    virtual void clearActions();

    /**
     * @brief The performing state.
     * @return True if there is currently an active action.
     */
    virtual bool isPerforming() const;

    /**
     * @brief Perform logic.
     * @param eData The environmental data.
     */
    virtual void logic(EnvironmentData& eData);

    private:
    /**
     * This is the action queue for this being.
     */
    ActionList mActions;
};

#endif /* ACTIONINTERFACE_HPP_ */
