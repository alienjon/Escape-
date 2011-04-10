/*
 * MessageWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */
#include "MessageWidget.hpp"

#include "../../Engine/Colors.hpp"
#include "../../Managers/FontManager.hpp"
#include "../../main.hpp"

using std::string;

const unsigned int MESSAGEWIDGET_TIMER_INTERVAL = 15;
const unsigned int MESSAGEWIDGET_STEP = 5;

MessageWidget::MessageWidget(const string& caption, const string& message) :
	mIsFoldingDown(false)
{
	// Configure the message (done first so it is underneath)
	mMessage.setFont(FontManager::get(FONT_TEXT));
	mMessage.setText(message);
	mMessage.setOpaque(false);
	mMessage.setFocusable(false);
	mMessage.setEditable(false);
	add(&mMessage);

	// Configure the caption.
	mCaption.setFont(FontManager::get(FONT_CAPTION));
	mCaption.setText(caption);
	mCaption.setOpaque(true);
	mCaption.setBackgroundColor(COLOR_MENU_DARK);
	mCaption.setFocusable(false);
	mCaption.setEditable(false);
	add(&mCaption);

	// Configure the widget.
	setOpaque(false);
	mTimer.start();
	setSize(mCaption.getWidth(), mCaption.getHeight());
	addMouseListener(this);
}

void MessageWidget::adjustSize()
{
	// Reset the texts based on the new width.
	mCaption.setText(formatStringToFit(mCaption.getText(), mCaption.getFont(), getWidth() - 10)); // The -10 is for the 'expanded' icon
	mCaption.setWidth(getWidth());
	mMessage.setText(formatStringToFit(mMessage.getText(), mMessage.getFont(), getWidth()));
	mMessage.setWidth(getWidth());
}

void MessageWidget::draw(gcn::Graphics* graphics)
{
	// Draw everything else first.
	gcn::Container::draw(graphics);

	// Centered verticaly, but to the right, draw a 'plus' sign if not folded down or a minus sign if folded down.
	graphics->setColor(COLOR_BLACK);
	graphics->drawLine(getWidth() - 8, (mCaption.getHeight() / 2), getWidth() - 2, (mCaption.getHeight() / 2)); // The 'minus' is drawn regardless.
	if(mIsFoldingDown)
	{
		graphics->drawLine(getWidth() - 5, (mCaption.getHeight() / 2) - 4, getWidth() - 5, (mCaption.getHeight() / 2) + 4);
	}
}

void MessageWidget::logic()
{
	// Only do logic if enough time has passed.
	if(mTimer.getTime() >= MESSAGEWIDGET_TIMER_INTERVAL)
	{
		// If folding down, then move downwards.
		if(mIsFoldingDown && mMessage.getY() != mCaption.getY() + mCaption.getHeight())
		{
			int y = mMessage.getY() + MESSAGEWIDGET_STEP;
			mMessage.setY((y > mCaption.getY() + mCaption.getHeight()) ? mCaption.getY() + mCaption.getHeight() : y);
			setHeight(mMessage.getY() + mMessage.getHeight());
			distributeActionEvent();
		}
		// If folding up, then move upwards.
		else if(!mIsFoldingDown && mMessage.getY() != mCaption.getY() + mCaption.getHeight() - mMessage.getHeight())
		{
			int y = mMessage.getY() - MESSAGEWIDGET_STEP;
			mMessage.setY((y < mCaption.getY() + mCaption.getHeight() - mMessage.getHeight()) ? mCaption.getY() + mCaption.getHeight() - mMessage.getHeight(): y);
			setHeight(mMessage.getY() + mMessage.getHeight());
			distributeActionEvent();
		}

		// Restart the timer.
		mTimer.start();
	}

	// Perform container logic first.
	gcn::Container::logic();
}

void MessageWidget::mousePressed(gcn::MouseEvent& event)
{
	// If the mouse was pressed within the caption's area, then fold either up or down.
	if(mCaption.getDimension().isPointInRect(event.getX(), event.getY()))
	{
		mIsFoldingDown = !mIsFoldingDown;
	}
}

void MessageWidget::reset()
{
	// Reset to the initial positioning.
	mMessage.setY(mCaption.getY() + mCaption.getHeight() - mMessage.getHeight());
	mIsFoldingDown = false;
}
