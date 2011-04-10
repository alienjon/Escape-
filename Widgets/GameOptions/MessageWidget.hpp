/*
 * MessageWidget.hpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */
#ifndef MESSAGEWIDGET_HPP_
#define MESSAGEWIDGET_HPP_

#include <string>

#include "../../guichan.hpp"
#include "../../Engine/Timer.hpp"

/**
 * @brief A widget that displays a message.
 */
class MessageWidget : public gcn::Container, public gcn::MouseListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param caption The message caption.
	 * @param message The message itself.
	 */
	MessageWidget(const std::string& caption, const std::string& message);

	/**
	 * @brief Adjust the internal sizes of the widget.
	 */
	virtual void adjustSize();

	/**
	 * @brief Draw the widget.
	 * @param graphics The graphics object with which to write.
	 */
	virtual void draw(gcn::Graphics* graphics);

	/**
	 * @brief Perform message logic.
	 */
	virtual void logic();

	/**
	 * @brief Listen to mouse presses.
	 * @param event The mouse event.
	 */
	virtual void mousePressed(gcn::MouseEvent& event);

	/**
	 * @brief Reset the widget to its initial position.
	 */
	virtual void reset();

	private:
	/**
	 * The caption and message boxes.
	 */
	gcn::TextBox mCaption,
				 mMessage;

	/**
	 * True if folding down, false if folding up.
	 */
	bool mIsFoldingDown;

	/**
	 * The animation timer.
	 */
	Timer mTimer;
};

#endif /* MESSAGEWIDGET_HPP_ */
