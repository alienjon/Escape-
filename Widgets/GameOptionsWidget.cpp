/*
 * GameOptionsWidget.cpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */

#include "GameOptionsWidget.hpp"

#include "../Engine/Colors.hpp"
#include "../Managers/FontManager.hpp"
#include "../Engine/Logger.hpp"

using std::string;

GameOptionsWidget::GameOptionsWidget() : gcn::Window("GAME OPTIONS"),
	mListBox(&mListModel),
	mScrollArea(&mOptions, gcn::ScrollArea::SHOW_NEVER, gcn::ScrollArea::SHOW_ALWAYS)
{
    // Configure this widget.
    setBaseColor(COLOR_MENU_DARK);
    setBackgroundColor(COLOR_MENU_LIGHT);
    setFrameSize(2);
    setFont(FontManager::get(FONT_DEFAULT));
    setMovable(false);
    mListModel.addOption("Options");
    mListModel.addOption("Messages");
    mListModel.addOption("Tasks");
    mListBox.setSelected(0);

    // Configure the list box.
    mListBox.setOpaque(false);
    mListBox.setSelectionColor(COLOR_MENU_LIGHT);
    mListBox.addSelectionListener(this);
    add(&mListBox);

    // Configure the scroll area.
    mScrollArea.setOpaque(true);
    mScrollArea.setBaseColor(COLOR_MENU_DARK);
    mScrollArea.setBackgroundColor(COLOR_MENU_LIGHT);
    add(&mScrollArea);
}

void GameOptionsWidget::addMessage(const string& title, const string& message)
{
	mMessages.addMessage(title, message);
}

unsigned int GameOptionsWidget::addTask(const string& title, const string& message)
{
	return mTasks.addTask(title, message);
}

void GameOptionsWidget::adjustSize()
{
	// Set the sizes.
	mListBox.setSize(getWidth() / 3, getHeight());
	mScrollArea.setSize(getWidth() - mListBox.getWidth() - (getFrameSize() * 2), getHeight() - getTitleBarHeight());

	// Set the positions.
	mListBox.setPosition(0, 0);
	mScrollArea.setPosition(mListBox.getWidth(), 0);

	// Adjust the options size, but make sure the width is the width of the scroll area and the height is at least the height of the scroll area.
	mOptions.adjustSize();
	mOptions.setSize(mScrollArea.getWidth() - mScrollArea.getScrollbarWidth(), (mOptions.getHeight() > mScrollArea.getHeight()) ? mOptions.getHeight() : mScrollArea.getHeight());

	// Adjust the tasks.
	mTasks.setSize(mScrollArea.getWidth() - mScrollArea.getScrollbarWidth(), (mTasks.getHeight() > mScrollArea.getHeight()) ? mTasks.getHeight() : mScrollArea.getHeight());
	mTasks.adjustInternal();

	// Adjust the messages widget.
	mMessages.setSize(mScrollArea.getWidth() - mScrollArea.getScrollbarWidth(), (mMessages.getHeight() > mScrollArea.getHeight()) ? mMessages.getHeight() : mScrollArea.getHeight());
	mMessages.adjustSize();
}

void GameOptionsWidget::completeTask(unsigned int id)
{
	mTasks.completeTask(id);
}

void GameOptionsWidget::valueChanged(const gcn::SelectionEvent& event)
{
	// Get the currently selected option and switch the content based on that option.
	switch(mListBox.getSelected())
	{
		case 0:
		{
			mScrollArea.setContent(&mOptions);
			break;
		}
		case 1:
		{
			mScrollArea.setContent(&mMessages);
			break;
		}
		case 2:
		{
			mScrollArea.setContent(&mTasks);
			break;
		}
		default:
		{
			Logger::log("Invalid game option selected.");
		}
	}
}
