/*
 * TaskWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#ifndef TASKWIDGET_HPP_
#define TASKWIDGET_HPP_

#include <string>

#include "../../guichan.hpp"

/**
 * @brief A task widget displays a single task to complete.  For the widget to display several tasks then
 * @see TasksWidget.
 */
class TaskWidget : public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 * @param title The title of the task.
	 * @param message THe message of the task.
	 */
	TaskWidget(const std::string& title, const std::string& message);

	/**
	 * @brief Adjust the size of the widget.
	 */
	virtual void adjustSize();

	/**
	 * @brief Get the tasks id.
	 * @return This tasks id.
	 */
	virtual unsigned int getId() const;

	/**
	 * @brief Get the message.
	 * @return This task's message.
	 */
	virtual std::string getMessage() const;

	/**
	 * @brief Get the title of the task.
	 * @return The tasks title.
	 */
	virtual const std::string& getTitle() const;

	private:
	/**
	 * The ID counter.
	 */
	static unsigned int m_idCounter;

	/**
	 * This is the tasks ID.
	 */
	unsigned int mId;

	/**
	 * These are the widgets to display the task information.
	 */
	gcn::Label mTitle;
	gcn::TextBox mMessage;
};

#endif /* TASKWIDGET_HPP_ */
