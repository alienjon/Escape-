/*
 * PlayerDirectionSelectionWidget.hpp
 *
 *  Created on: Dec 7, 2011
 *      Author: alienjon
 */
#ifndef PLAYERDIRECTIONSELECTIONWIDGET_HPP_
#define PLAYERDIRECTIONSELECTIONWIDGET_HPP_

#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

#include "../Engine/Timer.hpp"

/**
 * @brief A widget to display available directions and to allow the player to select one.
 */
class PlayerDirectionSelectionWidget : public gcn::Container, public gcn::KeyListener
{
	public:
	/**
	 * @brief Default constructor.
	 */
	PlayerDirectionSelectionWidget();

	/**
	 * @brief Display the widget with the provided directions at the provided position.
	 * @param up If true, display the up arrow.
	 * @param down If true, display the down arrow.
	 * @param left If true, display the left arrow.
	 * @param right If true, display the right arrow.
	 */
	virtual void display(bool up, bool down, bool left, bool right);

	/**
	 * @brief A key was pressed.
	 * @param event The key event.
	 */
	virtual void keyPressed(gcn::KeyEvent& event);

	/**
	 * @brief Perform widget logic.
	 */
	virtual void logic();

	private:
	// The 4 displays.
	gcn::Icon mUpIcon, mDownIcon, mLeftIcon, mRightIcon;

	// The fade timer for the non-displaying icons.
	Timer mPauseTimer;
};

#endif /* PLAYERDIRECTIONSELECTIONWIDGET_HPP_ */
