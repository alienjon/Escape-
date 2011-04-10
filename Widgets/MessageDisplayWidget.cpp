/*
 * MessageDisplayWidget.cpp
 *
 *  Created on: Aug 19, 2009
 *      Author: alienjon
 */
#include "MessageDisplayWidget.hpp"

#include "../Engine/Colors.hpp"
#include "../Managers/FontManager.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

using std::string;

const string MESSAGEDISPLAYWIDGET_CONTINUETEXT = "Press SPACEBAR to continue.";
const unsigned int MESSAGEDISPLAYWIDGET_PADDING = 4;
const unsigned int MESSAGE_TIMER_INTERVAL = 15;

MessageDisplayWidget::MessageDisplayWidget() :
	mSpacePressed(false),
	mCurrentMessagePosition(0)
{
	// Configure the widget.
	setAlignment(gcn::Graphics::CENTER);
	setBaseColor(COLOR_MENU_DARK);
//	setFont(FontManager::get(FONT_CAPTION)); @todo Implement a different colored caption font.
	setFont(FontManager::get(FONT_DEFAULT));
	setTitleBarHeight(getFont()->getHeight());
	setPadding(MESSAGEDISPLAYWIDGET_PADDING);
	setFrameSize(2);
	setMovable(false);
	mSprite.setFocusable(false);
	mMessageTimer.start();
	add(&mSprite);

	//	mTextBox.setFont(FontManager::get(FONT_TEXT)); @todo need to implement a dialog font, a text font (true type)
	mTextBox.setFont(FontManager::get(FONT_DEFAULT));
	mTextBox.setOpaque(false);
	mTextBox.setEditable(false);
	mTextBox.setFocusable(false);
	add(&mTextBox);

	// mContinueText.setFont(FontManager::get(FONT_SUBTEXT)); @todo need to implement a subtext font, for minor notes and such (true type, same as FONT_TEXT but smaller pointsize)
	mContinueText.setFont(FontManager::get(FONT_DEFAULT));
	mContinueText.setText(MESSAGEDISPLAYWIDGET_CONTINUETEXT);
	mContinueText.setOpaque(false);
	mContinueText.setEditable(false);
	mContinueText.setFocusable(false);
	add(&mContinueText);
}

void MessageDisplayWidget::mUpdateText()
{
	// Set the text.
	mTextBox.setText(formatStringToFit(mFullMessage.substr(0, ++mCurrentMessagePosition),
					 mTextBox.getFont(),
					 getWidth() - mSprite.getWidth() - (MESSAGEDISPLAYWIDGET_PADDING * 2)));

	// Set the width to the greater of the continue text or the textbox plus the icon.
	// Set the height to the greater of the icon height or the textbox height plus the continue text height and the height of the caption.
	int spriteHeight = mSprite.getHeight() + mContinueText.getHeight() + MESSAGEDISPLAYWIDGET_PADDING + getTitleBarHeight(),
		textHeight   = mTextBox.getHeight() + mContinueText.getHeight() + MESSAGEDISPLAYWIDGET_PADDING + getTitleBarHeight();
	setHeight(spriteHeight > textHeight ? spriteHeight : textHeight);

	// Finally center the continue text at the bottom of the widget.
	mContinueText.setPosition(((getWidth() - (MESSAGEDISPLAYWIDGET_PADDING * 2)) / 2) - (mContinueText.getWidth() / 2),
							  getHeight() - mContinueText.getHeight() - mContinueText.getFrameSize() - getTitleBarHeight());
}

void MessageDisplayWidget::keyPressed(gcn::KeyEvent& event)
{
	// If the spacebar was pressed, then remember that.
	if(isVisible() && event.getKey().getValue() == gcn::Key::SPACE)
	{
		mSpacePressed = true;
	}
}

void MessageDisplayWidget::keyReleased(gcn::KeyEvent& event)
{
	// If the spacebar was pressed, then tell the listeners.
	if(mSpacePressed && isVisible() && event.getKey().getValue() == gcn::Key::SPACE)
	{
		// If the full message is not being shown, then show it.
		if(mCurrentMessagePosition != mFullMessage.size())
		{
			mCurrentMessagePosition = mFullMessage.size() - 1;
			mUpdateText();
		}
		// ... otherwise, distribute the action event (which will likely close this widget on the screen)
		else
		{
			distributeActionEvent();
		}
		mSpacePressed = false;
	}
}

void MessageDisplayWidget::logic()
{
	// If the timer has passed the interval, then update the text.
	if(mMessageTimer.getTime() >= MESSAGE_TIMER_INTERVAL && mCurrentMessagePosition != mFullMessage.size())
	{
		// Set the message text.
		mUpdateText();

		// Restart the timer.
		mMessageTimer.start();
	}

	// Pass to widget logic.
	gcn::Window::logic();
}

void MessageDisplayWidget::set(const string& caption, const string& message, const Sprite& sprite)
{
	// Set the data.
	mCurrentMessagePosition = 0;
	mTextBox.setText("");
	mFullMessage = message;
	setCaption(caption);
	mSprite.setSprite(sprite);
	mTextBox.setPosition(mSprite.getX() + mSprite.getWidth() + MESSAGEDISPLAYWIDGET_PADDING, 0);
}
