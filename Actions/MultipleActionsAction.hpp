/*
 * MultipleActionsAction.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */

#ifndef MULTIPLEACTIONSACTION_HPP_
#define MULTIPLEACTIONSACTION_HPP_

#include "../Actions/Action.hpp"

/**
 * @brief An action that performs multiple, other actions.
 */
class MultipleActionsAction : public Action
{
    public:
    /**
     * @brief Performs multiple actions as one action.
     * @param actions The list of actions to perform at once.
     * @note This action will not be performed until all of its children have been performed.
     */
    MultipleActionsAction(ActionList* actions);
    virtual ~MultipleActionsAction();

    /**
     * Activate the actions all at once.
     * @param eData The environment data.
     * @note Even if some actions are performed immediately, the MultipleActionsAction will not be performed until ALL of the actions have been performed.
     */
    virtual void activate(EnvironmentData& eData);

    protected:
    /**
     * The list of actions to perform.
     */
    ActionList* mActions;
};

#endif /* MULTIPLEACTIONSACTION_HPP_ */
