/*
 * MessagesWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#include "MessagesWidget.hpp"

using std::list;
using std::string;

MessagesWidget::MessagesWidget()
{
	setOpaque(false);
}

MessagesWidget::~MessagesWidget()
{
	for(list<MessageWidget*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
	{
		delete *it;
	}
}

void MessagesWidget::action(const gcn::ActionEvent& action)
{
	adjustSize(false);
}

void MessagesWidget::addMessage(const string& caption, const string& message)
{
	MessageWidget* widget = new MessageWidget(caption, message);
	widget->addActionListener(this);
	add(widget);
	mMessages.push_back(widget);
	adjustSize();
}

void MessagesWidget::adjustSize(bool reset)
{
	unsigned int height = 0;
	for(list<MessageWidget*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
	{
		(*it)->setWidth(getWidth());
		(*it)->adjustSize();
		if(reset)
		{
			(*it)->reset(); // Reset to the initial position when the width has changed.
		}
		(*it)->setY(height);
		height += (*it)->getHeight();
	}
	setHeight(height);
}
