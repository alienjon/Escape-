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
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    protected:
    // The list of actions to perform.
    ActionList* mActions;
};

#endif /* MULTIPLEACTIONSACTION_HPP_ */
