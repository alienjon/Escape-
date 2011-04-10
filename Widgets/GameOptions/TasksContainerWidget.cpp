/*
 * TasksContainerWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#include "TasksContainerWidget.hpp"

#include "../../Engine/Logger.hpp"
#include "../../main.hpp"

using std::list;
using std::string;

TasksContainerWidget::TasksContainerWidget()
{
	setOpaque(false);
}

TasksContainerWidget::~TasksContainerWidget()
{
	gcn::Container::clear();
	for(list<TaskWidget*>::iterator it = mTasks.begin(); it != mTasks.end(); ++it)
	{
		delete *it;
	}
}

unsigned int TasksContainerWidget::addTask(const std::string& title, const std::string& message)
{
	TaskWidget* task = new TaskWidget(title, message);
	task->setWidth(getWidth());
	add(task, 0, getHeight());
	mTasks.push_back(task);
	setHeight(getHeight() + task->getHeight());
	return task->getId();
}

void TasksContainerWidget::adjustSize()
{
	// Adjust the size of the internals.
	setHeight(0);
	for(list<TaskWidget*>::iterator it = mTasks.begin(); it != mTasks.end(); ++it)
	{
		(*it)->setWidth(getWidth());
		(*it)->adjustSize();
		(*it)->setY(getHeight());
		setHeight(getHeight() + (*it)->getHeight());
	}
}

TaskWidget* TasksContainerWidget::getTask(unsigned int id) const
{
	// Find the widget.
	for(list<TaskWidget*>::const_iterator it = mTasks.begin(); it != mTasks.end(); ++it)
	{
		if((*it)->getId() == id)
		{
			return *it;
		}
	}

	return 0;
}

void TasksContainerWidget::removeTask(unsigned int id)
{
	// First, find the widget.
	TaskWidget* task = getTask(id);

	// If a task was found, then remove it and delete it.
	if(task)
	{
		remove(task);
		mTasks.remove(task);
		setHeight(getHeight() - task->getHeight());
		delete task;
	}
	// Otherwise, log an error.
	else
	{
		Logger::error("Task with id '" + toString(id) + "' doesn't exist.  Cannot remove.");
	}
}
