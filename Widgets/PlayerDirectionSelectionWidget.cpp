/*
 * PlayerDirectionSelectionWidget.cpp
 *
 *  Created on: Dec 7, 2011
 *      Author: alienjon
 */
#include "PlayerDirectionSelectionWidget.hpp"

#include <string>

#include "../Engine/Colors.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"
#include "../Engine/VideoManager.hpp"

using std::string;

const unsigned int PDS_WIDGET_FRAMESIZE = 1;

PlayerDirectionSelectionWidget::PlayerDirectionSelectionWidget() :
	mUpIcon(IMAGE_DIRECTIONAL_ARROW_UP),
	mDownIcon(IMAGE_DIRECTIONAL_ARROW_DOWN),
	mLeftIcon(IMAGE_DIRECTIONAL_ARROW_LEFT),
	mRightIcon(IMAGE_DIRECTIONAL_ARROW_RIGHT)
{
	// Add and set the positions of the icons.
	add(&mUpIcon, mLeftIcon.getWidth() * 2, PDS_WIDGET_FRAMESIZE);
	add(&mDownIcon, mLeftIcon.getWidth() * 2, mUpIcon.getHeight() * 4);
	add(&mLeftIcon, PDS_WIDGET_FRAMESIZE, mUpIcon.getHeight() * 2);
	add(&mRightIcon, mLeftIcon.getWidth() * 4, mUpIcon.getHeight() * 2);

	// Configure the icons.
	mUpIcon.setVisible(false);
	mUpIcon.setBaseColor(gcn::COLOR_GREEN);
	mDownIcon.setVisible(false);
	mDownIcon.setBaseColor(gcn::COLOR_GREEN);
	mLeftIcon.setVisible(false);
	mLeftIcon.setBaseColor(gcn::COLOR_GREEN);
	mRightIcon.setVisible(false);
	mRightIcon.setBaseColor(gcn::COLOR_GREEN);

	// Other configuration.
	setOpaque(false);
	setVisible(false);
	setFocusable(true);

	// Set the size of the widget.
	setSize(mLeftIcon.getWidth() * 5 + (PDS_WIDGET_FRAMESIZE * 2), mUpIcon.getHeight() * 5 + (PDS_WIDGET_FRAMESIZE * 2));
}

void PlayerDirectionSelectionWidget::display(bool up, bool down, bool left, bool right)
{
	// Display the arrows for the selected directions 48px from the center pos in their respective directions.
	setVisible(true);
	if(up)
		mUpIcon.setVisible(true);
	if(down)
		mDownIcon.setVisible(true);
	if(left)
		mLeftIcon.setVisible(true);
	if(right)
		mRightIcon.setVisible(true);
}

void PlayerDirectionSelectionWidget::keyPressed(gcn::KeyEvent& event)
{
	int key = event.getKey().getValue();
	if(isVisible() && !mPauseTimer.isStarted() &&
	   (key == gcn::Key::UP || key == gcn::Key::DOWN || key == gcn::Key::LEFT || key == gcn::Key::RIGHT))
	{
		if(key == gcn::Key::UP)
			mUpIcon.setFrameSize(1);
		else if(key == gcn::Key::DOWN)
			mDownIcon.setFrameSize(1);
		else if(key == gcn::Key::LEFT)
			mLeftIcon.setFrameSize(1);
		else if(key == gcn::Key::RIGHT)
			mRightIcon.setFrameSize(1);
		mPauseTimer.start();
	}
}

void PlayerDirectionSelectionWidget::logic()
{
	if(mPauseTimer.isStarted() && mPauseTimer.getTime() >= 200)
	{
		// Stop the timer, hide everything, and release focus.
		mPauseTimer.stop();
		mUpIcon.setVisible(false);
		mDownIcon.setVisible(false);
		mLeftIcon.setVisible(false);
		mRightIcon.setVisible(false);
		setVisible(false);

		// Set and distribute the action event.
		string dir = "right";
		if(mUpIcon.getFrameSize())
			dir = "up";
		else if(mDownIcon.getFrameSize())
			dir = "down";
		else if(mLeftIcon.getFrameSize())
			dir = "left";
		setActionEventId(ACTION_DIRECTION_SELECTED + ":" + dir);
		distributeActionEvent();

		// Unset the frame sizes.
		mUpIcon.setFrameSize(0);
		mDownIcon.setFrameSize(0);
		mLeftIcon.setFrameSize(0);
		mRightIcon.setFrameSize(0);
	}

	gcn::Container::logic();
}
