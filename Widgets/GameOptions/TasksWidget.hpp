/*
 * TasksWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#ifndef TASKSWIDGET_HPP_
#define TASKSWIDGET_HPP_

#include <list>
#include <string>

#include "../../guichan.hpp"
#include "../../Widgets/GameOptions/TasksContainerWidget.hpp"

/**
 * @brief This widget lists tasks for the player to complete.
 */
class TasksWidget : public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 */
	TasksWidget();

	/**
	 * @brief Add a task.
	 * @param title The title of the task to complete.
	 * @param message The details for completing the task.
	 * @return The ID of the task.
	 */
	virtual unsigned int addTask(const std::string& title, const std::string& message);

	/**
	 * @brief Adjust the internals of the widget.
	 */
	virtual void adjustInternal();

	/**
	 * @brief Move a task from 'to be completed' to 'completed'.
	 * @param id The ID of the task to complete.
	 */
	virtual void completeTask(unsigned int id);

	private:
	/**
	 * These are the labels for the to be completed/completed tasks.
	 */
	gcn::Label mToCompleteLabel,
			   mCompletedLabel;

	/**
	 * These containers hold the to complete and completed tasks.
	 */
	TasksContainerWidget mToCompleteContainer,
						 mCompletedContainer;
};

#endif /* TASKSWIDGET_HPP_ */
