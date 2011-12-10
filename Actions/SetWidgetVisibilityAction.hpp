/*
 * SetWidgetVisibilityAction.hpp
 *
 *  Created on: Aug 6, 2009
 *      Author: alienjon
 */
#ifndef SETWIDGETVISIBILITYACTION_HPP_
#define SETWIDGETVISIBILITYACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Engine/guichan.hpp"

/**
 * @brief An action that sets the visibility status of a widget.
 */
class SetWidgetVisibilityAction : public Action
{
    public:
    /**
     * @brief Set the visibility state of a widget.
     * @param widget The widget.
     * @param state The state to set.
     */
    SetWidgetVisibilityAction(gcn::Widget& widget, bool state);

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    private:
    // The widget.
    gcn::Widget& mWidget;

    // The state.
    bool mState;
};

#endif /* SETWIDGETVISIBILITYACTION_HPP_ */
