/*
 * Action.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */

#ifndef ACTION_HPP_
#define ACTION_HPP_

#include <list>

class EnvironmentData;

/**
 * @brief An action is a single act that can be performed in such a way so that it can be placed in a list an acted in a certain order.
 */
class Action
{
    public:
    virtual ~Action()
    {}

    /**
     * @brief Activate this action.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData) = 0;

    /**
     * @brief Return true if this action has been performed.
     * @return True if the action is finished performing.
     */
    virtual bool isPerformed()
    {
        return mPerformed;
    }

    protected:
    /**
     * @brief Actions must be implemented via subclasses.
     */
    Action() : mPerformed(false), mActivated(false)
    {}

    /**
     * The state of performance of this action.
     */
    bool mPerformed;

    /**
     * The state of activation for this action.
     */
    bool mActivated;
};

/**
 * This is a list of actions.
 */
typedef std::list<Action*> ActionList;

#endif /* ACTION_HPP_ */
