/*
 * GUIMessageWidget.hpp
 *
 *  Created on: Aug 27, 2009
 *      Author: alienjon
 */

#ifndef GUIMESSAGEWIDGET_HPP_
#define GUIMESSAGEWIDGET_HPP_

#include <string>

#include "../guichan.hpp"

#include "../Engine/Timer.hpp"

/*
 * @brief Used to display an in-game message to the user for a specified period of time.
 */
class GUIMessageWidget : public gcn::Container
{
    public:
    /**
     * @brief Construct a GUI message widget.
     */
    GUIMessageWidget();

    /**
     * @brief Display a message.
     * @param message The message to display.
     * @param duration The length of time to have the message on the screen.
     */
    virtual void displayMessage(const std::string& message, unsigned int duration);

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    private:
    /**
     * The label itself.
     */
    gcn::Label mLabel;

    /**
     * The timer.
     */
    Timer mTimer;

    /**
     * The duration.
     */
    unsigned int mDuration;
};

#endif /* GUIMESSAGEWIDGET_HPP_ */
