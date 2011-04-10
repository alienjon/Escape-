/*
 * GUIMessageWidget.cpp
 *
 *  Created on: Aug 27, 2009
 *      Author: alienjon
 */

#include "GUIMessageWidget.hpp"

#include "../Engine/Colors.hpp"
#include "../Managers/FontManager.hpp"

using std::string;

GUIMessageWidget::GUIMessageWidget() : mDuration(0)
{
    // Configure the label.
    mLabel.setFont(FontManager::get(FONT_MENU_INACTIVE));
    mLabel.adjustSize();

    // Configure this widget.
    setBaseColor(COLOR_MENU_DARK);
    setFrameSize(2);
    setOpaque(true);
    setSize(mLabel.getWidth(), mLabel.getHeight());
    setVisible(false);
    add(&mLabel);
}

void GUIMessageWidget::displayMessage(const string& message, unsigned int duration)
{
    // Set the duration and message, hide the widget and start the timer.
    mDuration = duration;
    mLabel.setCaption(message);
    mLabel.adjustSize(); // Need to adjust the size of the widget after changing the caption.
    setSize(mLabel.getWidth(), mLabel.getHeight());
    setVisible(true);
    mTimer.start();
}

void GUIMessageWidget::logic()
{
    // If the time has expired then hide the widget and stop the timer.
    if(mTimer.isStarted() && mTimer.getTime() >= mDuration)
    {
        setVisible(false);
        mTimer.stop();
    }

    // Perform the rest of the logic.
    Container::logic();
}
