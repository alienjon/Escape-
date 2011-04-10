/*
 * GameOptionsWidget.hpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */

#ifndef GAMEOPTIONSWIDGET_HPP_
#define GAMEOPTIONSWIDGET_HPP_

#include <string>

#include "../Widgets/GameOptionsListModel.hpp"
#include "../Widgets/GameOptions/GameSettingsWidget.hpp"
#include "../guichan.hpp"
#include "../Widgets/GameOptions/MessagesWidget.hpp"
#include "../Widgets/GameOptions/TasksWidget.hpp"

/**
 * @brief A widget to display the in-game options menu.
 */
class GameOptionsWidget : public gcn::SelectionListener, public gcn::Window
{
    public:
    /**
     * @brief The game options widget shows in-game options for the player.
     */
    GameOptionsWidget();

    /**
     * @brief Add a message to be displayed in the messages list.
     * @param title The messages title.
     * @param message The message itself.
     */
    virtual void addMessage(const std::string& title, const std::string& message);

    /**
     * @brief Add a task to be completed.
     * @param title The title for the task.
     * @param message The detailed message for the task.
     * @return The ID of the task.
     */
    virtual unsigned int addTask(const std::string& title, const std::string& message);

    /**
     * @brief Adjust the size of the widget.
     */
    virtual void adjustSize();

    /**
     * @brief Complete a task.
     * @param id The id of the task that is to be completed.
     */
    virtual void completeTask(unsigned int id);

    /**
     * @brief A value has changed.
     * @param event The selection event.
     */
    virtual void valueChanged(const gcn::SelectionEvent& event);

    private:
    /**
     * The game options list.
     */
    GameOptionsListModel mListModel;
    gcn::ListBox mListBox;

    /**
     * This is the display area.
     */
    GameSettingsWidget mOptions;
	TasksWidget mTasks;
	MessagesWidget mMessages;
    gcn::ScrollArea mScrollArea;
};

#endif /* GAMEOPTIONSWIDGET_HPP_ */
