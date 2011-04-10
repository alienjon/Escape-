/*
 * TasksContainerWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#ifndef TASKSCONTAINERWIDGET_HPP_
#define TASKSCONTAINERWIDGET_HPP_

#include <list>
#include <string>

#include "../../guichan.hpp"
#include "../../Widgets/GameOptions/TaskWidget.hpp"

class TasksContainerWidget : public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 */
	TasksContainerWidget();
	virtual ~TasksContainerWidget();

	/**
	 * @brief Add a task to the widget.
	 * @param title The title of the task.
	 * @param message The message of the task.
	 * @return The ID of the task.
	 */
	virtual unsigned int addTask(const std::string& title, const std::string& message);

	/**
	 * @brief Adjust the size of the widget.
	 */
	virtual void adjustSize();

	/**
	 * @brief Get the task with the provided id.
	 * @param id The id of the task.
	 * @return The requested task.
	 */
	virtual TaskWidget* getTask(unsigned int id) const;

	/**
	 * @brief Remove a task from the widget.
	 * @param id The ID of the widget.
	 */
	virtual void removeTask(unsigned int id);

	private:
	/**
	 * The collection of tasks.
	 */
	std::list<TaskWidget*> mTasks;
};

#endif /* TASKSCONTAINERWIDGET_HPP_ */
