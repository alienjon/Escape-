/*
 * MessageDisplayWidget.hpp
 *
 *  Created on: Aug 19, 2009
 *      Author: alienjon
 */
#ifndef MESSAGEDISPLAYWIDGET_HPP_
#define MESSAGEDISPLAYWIDGET_HPP_

#include <string>

#include "../guichan.hpp"
#include "../Engine/Sprite.hpp"
#include "../Widgets/SpriteWidget.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A widget which displays text.  Intended to display tutorial messages/dialog
 */
class MessageDisplayWidget : public gcn::KeyListener, public gcn::Window
{
	public:
	/**
	 * @brief Default constructor.
	 */
	MessageDisplayWidget();

	/**
	 * @brief Listen for key presses.
	 * @param event The key event.
	 */
	virtual void keyPressed(gcn::KeyEvent& event);

	/**
	 * @brief Listen for key releases.
	 * @param event The key event.
	 */
	virtual void keyReleased(gcn::KeyEvent& event);

	/**
	 * @brief The widget's logic.
	 */
	virtual void logic();

	/**
	 * @brief Show text on the screen.
	 * @param caption The caption.
	 * @param message The message to display.
	 * @param sprite The sprite to display with the text.
	 */
	virtual void set(const std::string& caption, const std::string& message, const Sprite& sprite);

	private:
	/**
	 * @brief Update the text with its current position.
	 */
	void mUpdateText();

	/**
	 * An image to display as part of this widget.
	 */
	SpriteWidget mSprite;

	/**
	 * The text boxes to display.
	 */
	gcn::TextBox mTextBox;

	/**
	 * The 'press to continue' text.
	 */
	gcn::TextBox mContinueText;

	/**
	 * Keeps track of when the space bar is pressed so that the widget doesn't close without having received the keypress in the first place.
	 */
	bool mSpacePressed;

	/**
	 * This is the full message.
	 */
	std::string mFullMessage;

	/**
	 * This is the position in the full message being displayed right now.
	 */
	std::string::size_type mCurrentMessagePosition;

	/**
	 * This is the message timer.
	 */
	Timer mMessageTimer;
};

#endif /* MESSAGEDISPLAYWIDGET_HPP_ */
