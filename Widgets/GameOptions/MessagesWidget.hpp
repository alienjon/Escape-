/*
 * MessagesWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#ifndef MESSAGESWIDGET_HPP_
#define MESSAGESWIDGET_HPP_

#include <list>
#include <string>

#include "../../guichan.hpp"
#include "../../Widgets/GameOptions/MessageWidget.hpp"

/**
 * @brief A widget that holds a list of messages.
 */
class MessagesWidget : public gcn::ActionListener, public gcn::Container
{
	public:
	/**
	 * @brief Default constructor.
	 */
	MessagesWidget();
	virtual ~MessagesWidget();

	/**
	 * @brief An action was performed by one of the messages.
	 * @param event The action event.
	 */
	virtual void action(const gcn::ActionEvent& event);

	/**
	 * @brief Add a message.
	 * @param caption The message caption.
	 * @param message The message itself.
	 */
	virtual void addMessage(const std::string& caption, const std::string& message);

	/**
	 * @brief Adjust the width of the internal messages to the this widget's size and the height of the widget based on the internal message sizes.
	 * @param reset Pass TRUE if you want to reset all the message widget's to their initial position after a adjusting the size.
	 */
	virtual void adjustSize(bool reset = true);

	private:
	/**
	 * The list of messages.
	 */
	std::list<MessageWidget*> mMessages;
};

#endif /* MESSAGESWIDGET_HPP_ */
