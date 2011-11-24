///*
// * SetWidgetVisibilityAction.cpp
// *
// *  Created on: Aug 6, 2009
// *      Author: alienjon
// */
//#include "SetWidgetVisibilityAction.hpp"
//
//#include <stdexcept>
//
//SetWidgetVisibilityAction::SetWidgetVisibilityAction(gcn::Widget* widget, bool state) : mWidget(widget),
//                                                                                        mState(state)
//{
//    // Make sure the widget exists.
//    if(!mWidget)
//    {
//        throw std::runtime_error("SetWidgetVisbilityAction() -> Null widget provided.");
//    }
//}
//
//void SetWidgetVisibilityAction::activate(Level& level)
//{
//    // Set the widget's visibility and consider yourself performed!
//    mWidget->setVisible(mState);
//    mPerformed = true;
//}
