/*
 * SetWidgetVisibilityAction.cpp
 *
 *  Created on: Aug 6, 2009
 *      Author: alienjon
 */
#include "SetWidgetVisibilityAction.hpp"

SetWidgetVisibilityAction::SetWidgetVisibilityAction(gcn::Widget& widget, bool state) :
	mWidget(widget),
    mState(state)
{
}

void SetWidgetVisibilityAction::activate(Level& level)
{
    // Set the widget's visibility and consider yourself performed!
    mWidget.setVisible(mState);
    mActivated = true;
    mPerformed = true;
}
