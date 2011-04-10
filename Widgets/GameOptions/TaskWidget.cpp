/*
 * TaskWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#include "TaskWidget.hpp"

#include "../../Managers/FontManager.hpp"
#include "../../main.hpp"

using std::string;

TaskWidget::TaskWidget(const string& title, const string& message) :
	mId(m_idCounter++),
	mTitle(title),
	mMessage(message)
{
	// Configure the widget.
	setOpaque(false);

	// Set the fonts.
	mTitle.setFont(FontManager::get(FONT_CAPTION));
	mTitle.adjustSize();
	mTitle.setFocusable(false);
	mMessage.setFont(FontManager::get(FONT_TEXT));
	mMessage.setOpaque(false);
	mMessage.setEditable(false);
	mMessage.setFocusable(false);

	// Add the widgets.
	add(&mTitle);
	add(&mMessage);
}

void TaskWidget::adjustSize()
{
	// Make sure the message is on the right side.
	mMessage.setText(formatStringToFit(mMessage.getText(), mMessage.getFont(), getWidth() * 7 / 8));
	mMessage.setPosition(getWidth() - mMessage.getWidth(), mTitle.getHeight());

	// Set the height to compensate.
	setHeight(mTitle.getHeight() + mMessage.getHeight());
}

unsigned int TaskWidget::getId() const
{
	return mId;
}

string TaskWidget::getMessage() const
{
	return mMessage.getText();
}

const string& TaskWidget::getTitle() const
{
	return mTitle.getCaption();
}

unsigned int TaskWidget::m_idCounter = 0;
