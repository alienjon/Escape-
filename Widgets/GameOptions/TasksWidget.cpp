/*
 * TasksWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */
#include "TasksWidget.hpp"

#include "../../Managers/FontManager.hpp"
#include "../../Engine/Logger.hpp"
#include "../../main.hpp"
#include "../../Widgets/GameOptions/TaskWidget.hpp"

using std::string;

TasksWidget::TasksWidget() :
	mToCompleteLabel("Current Tasks"),
	mCompletedLabel("Completed Tasks")
{
	// Configure the widget.
	setOpaque(false);

	// Set the fonts.
	mToCompleteLabel.setFont(FontManager::get(FONT_CAPTION));
	mCompletedLabel.setFont(FontManager::get(FONT_CAPTION));
	mToCompleteLabel.adjustSize();
	mCompletedLabel.adjustSize();

	// Configure and add the containers.
	add(&mToCompleteLabel);
	add(&mCompletedLabel);
	add(&mToCompleteContainer);
	add(&mCompletedContainer);

	// Adjust the initial internal positions.
	adjustInternal();
}

unsigned int TasksWidget::addTask(const string& title, const string& message)
{
	unsigned int id = mToCompleteContainer.addTask(title, message);
	adjustInternal();
	return id;
}

void TasksWidget::adjustInternal()
{
	// Set the internal sizes.
	mToCompleteContainer.setWidth(getWidth());
	mCompletedContainer.setWidth(getWidth());
	mToCompleteContainer.adjustSize();
	mCompletedContainer.adjustSize();

	// Set the height.
	setHeight(mToCompleteLabel.getHeight() + mToCompleteContainer.getHeight() + mCompletedLabel.getHeight() + mCompletedContainer.getHeight() + 10);

	// Resize the internal containers as well as the object inside them.
	mToCompleteLabel.setPosition((getWidth() / 2) - (mToCompleteLabel.getWidth() / 2), 0);
	mToCompleteContainer.setPosition(0, mToCompleteLabel.getY() + mToCompleteLabel.getHeight());
	mCompletedLabel.setPosition((getWidth() / 2) - (mCompletedLabel.getWidth() / 2), mToCompleteContainer.getY() + mToCompleteContainer.getHeight() + 10);
	mCompletedContainer.setPosition(0, mCompletedLabel.getY() + mCompletedLabel.getHeight());
}

void TasksWidget::completeTask(unsigned int id)
{
	// Get the task with the provided ID.
	TaskWidget* task = mToCompleteContainer.getTask(id);
	if(task)
	{
		// Add the task to the completed container.  (Do this first, as it is deleted once it is removed)
		mCompletedContainer.addTask(task->getTitle(), task->getMessage());

		// Remove the task from the 'to complete'.
		mToCompleteContainer.removeTask(id);

		// Adjust the internals.
		adjustInternal();
	}
	else
	{
		Logger::log("No task exists with id '" + toString(id) + "'.  Unable to complete task.");
	}
}
