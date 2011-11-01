/*
 * LevelCompleteWidget.cpp
 *
 *  Created on: Oct 11, 2011
 *      Author: alienjon
 */
#include "LevelCompleteWidget.hpp"

#include "../Engine/Colors.hpp"
#include "../Managers/FontManager.hpp"
#include "../main.hpp"

using std::string;

const unsigned int LEVELCOMPLETEWIDGET_TIMERINTERVAL = 1500;
#include <iostream>
using namespace std;
LevelCompleteWidget::LevelCompleteWidget()
{
	// Configure the widget.
	addKeyListener(this);
	setFocusable(true);
	setOpaque(true);
	setBaseColor(COLOR_WHITE);
	setFrameSize(2);

	// Configure the fonts.
	//@todo I probably want to get new fonts for these to make them look better.
	mCaption.setFont(FontManager::get(FONT_CAPTION));
	mTimeLabel.setFont(FontManager::get(FONT_DEFAULT));
	mTimeValue.setFont(FontManager::get(FONT_TEXT));
	mTimeBonus.setFont(FontManager::get(FONT_DEFAULT));
	mMapLabel.setFont(FontManager::get(FONT_DEFAULT));
	mMapValue.setFont(FontManager::get(FONT_TEXT));
	mMapBonus.setFont(FontManager::get(FONT_DEFAULT));
	mDifficultyLabel.setFont(FontManager::get(FONT_DEFAULT));
	mDifficultyValue.setFont(FontManager::get(FONT_TEXT));
	mDifficultyBonus.setFont(FontManager::get(FONT_DEFAULT));
	mBaseScoreLabel.setFont(FontManager::get(FONT_DEFAULT));
	mBaseScoreValue.setFont(FontManager::get(FONT_DEFAULT));
	mBonusScoreLabel.setFont(FontManager::get(FONT_DEFAULT));
	mBonusScoreValue.setFont(FontManager::get(FONT_DEFAULT));
	mTotalScoreLabel.setFont(FontManager::get(FONT_DEFAULT));
	mTotalScoreValue.setFont(FontManager::get(FONT_DEFAULT));
	mMessage.setFont(FontManager::get(FONT_TEXT));

	// Set the labels.
	mTimeLabel.setCaption("Time Completed: ");
	mMapLabel.setCaption("Maze Complexity: ");
	mDifficultyLabel.setCaption("Difficulty: ");
	mBaseScoreLabel.setCaption("Base Score: ");
	mBonusScoreLabel.setCaption("Bonus Score: ");
	mTotalScoreLabel.setCaption("Total Score: ");
	mMessage.setCaption("press space to continue");

	// Adjust the sizes.
	mTimeLabel.adjustSize();
	mMapLabel.adjustSize();
	mDifficultyLabel.adjustSize();
	mBaseScoreLabel.adjustSize();
	mBonusScoreLabel.adjustSize();
	mTotalScoreLabel.adjustSize();
	mMessage.adjustSize();

	// Make all the values and bonus' and the message labels invisible initially.
	mTimeValue.setVisible(false);
	mTimeBonus.setVisible(false);
	mMapValue.setVisible(false);
	mMapBonus.setVisible(false);
	mDifficultyValue.setVisible(false);
	mDifficultyBonus.setVisible(false);
	mBaseScoreValue.setVisible(false);
	mBonusScoreValue.setVisible(false);
	mTotalScoreValue.setVisible(false);
	mMessage.setVisible(false);

	// Add all of the widgets.
	add(&mCaption);
	add(&mTimeLabel);
	add(&mTimeValue);
	add(&mTimeBonus);
	add(&mMapLabel);
	add(&mMapValue);
	add(&mMapBonus);
	add(&mDifficultyLabel);
	add(&mDifficultyValue);
	add(&mDifficultyBonus);
	add(&mBaseScoreLabel);
	add(&mBaseScoreValue);
	add(&mBonusScoreLabel);
	add(&mBonusScoreValue);
	add(&mTotalScoreLabel);
	add(&mTotalScoreValue);
	add(&mMessage);
}

LevelCompleteWidget::~LevelCompleteWidget()
{
	removeKeyListener(this);
}

void LevelCompleteWidget::adjust()
{
	// Calculate the X position for the value and bonus labels.
	int labelX = 0, valueX = 0, bonusX;
	labelX = (mTimeLabel.getWidth() > mMapLabel.getWidth()) ? mTimeLabel.getWidth() : mMapLabel.getWidth();
	labelX = (labelX > mDifficultyLabel.getWidth()) ? labelX : mDifficultyLabel.getWidth();
	valueX = (mTimeValue.getWidth() > mMapValue.getWidth()) ? mTimeValue.getWidth() : mMapValue.getWidth();
	valueX = (valueX > mDifficultyValue.getWidth()) ? valueX : mDifficultyValue.getWidth();
	valueX = (valueX > mBaseScoreValue.getWidth()) ? valueX : mBaseScoreValue.getWidth();
	valueX = (valueX > mBonusScoreValue.getWidth()) ? valueX : mBonusScoreValue.getWidth();
	valueX = (valueX > mTotalScoreValue.getWidth()) ? valueX : mTotalScoreValue.getWidth();
	bonusX = (mTimeBonus.getWidth() > mMapBonus.getWidth()) ? mTimeBonus.getWidth() : mMapBonus.getWidth();
	bonusX = (bonusX > mDifficultyBonus.getWidth()) ? bonusX : mDifficultyBonus.getWidth();
	bonusX = (bonusX > mBaseScoreValue.getWidth()) ? bonusX : mBaseScoreValue.getWidth();
	bonusX = (bonusX > mBonusScoreValue.getWidth()) ? bonusX : mBonusScoreValue.getWidth();
	bonusX = (bonusX > mTotalScoreValue.getWidth()) ? bonusX : mTotalScoreValue.getWidth();

	// Add a space between the segments.
	valueX += 4;
	valueX += 4;

	// Set the positions.
	mTimeLabel.setPosition(0, mCaption.getY() + mCaption.getHeight() + 6);
	mTimeValue.setPosition(labelX, mTimeLabel.getY());
	mTimeBonus.setPosition(labelX + valueX, mTimeLabel.getY());

	mMapLabel.setPosition(0, mTimeLabel.getY() + mTimeLabel.getHeight());
	mMapValue.setPosition(labelX, mMapLabel.getY());
	mMapBonus.setPosition(labelX + valueX, mMapLabel.getY());

	mDifficultyLabel.setPosition(0, mMapLabel.getY() + mMapLabel.getHeight());
	mDifficultyValue.setPosition(labelX, mDifficultyLabel.getY());
	mDifficultyBonus.setPosition(labelX + valueX, mDifficultyLabel.getY());

	mBaseScoreLabel.setPosition(0, mDifficultyLabel.getY() + mDifficultyLabel.getHeight() + 10);
	mBaseScoreValue.setPosition(labelX + valueX, mBaseScoreLabel.getY());

	mBonusScoreLabel.setPosition(0, mBaseScoreLabel.getY() + mBaseScoreLabel.getHeight());
	mBonusScoreValue.setPosition(labelX + valueX, mBonusScoreLabel.getY());

	mTotalScoreLabel.setPosition(0, mBonusScoreLabel.getY() + mBonusScoreLabel.getHeight());
	mTotalScoreValue.setPosition(labelX + valueX, mTotalScoreLabel.getY());

	// Configure the size.
	setWidth(labelX + valueX + bonusX);

	// The caption and message go last, as they are based on the size.
	mCaption.setPosition(getWidth() / 2 - mCaption.getWidth() / 2, 0);
	mMessage.setPosition(getWidth() / 2 - mMessage.getWidth() / 2, mTotalScoreLabel.getY() + mTotalScoreLabel.getHeight() + 8);

	// Set the height.
	setHeight(mMessage.getY() + mMessage.getHeight());
}

void LevelCompleteWidget::display(const string& message,
								  unsigned int timeValue, unsigned int timeBonus, unsigned int mapValue, unsigned int mapBonus,
								  unsigned int difficultyValue, double difficultyBonus, unsigned int base, unsigned int bonus, unsigned int total)
{
	// Oh right, actually show the widget.
	setVisible(true);

	// Set the values for the labels.
	mCaption.setCaption(message);
	mTimeValue.setCaption(toString(timeValue));
	mTimeBonus.setCaption(toString(timeBonus));
	mMapValue.setCaption(toString(mapValue));
	mMapBonus.setCaption(toString(mapBonus));
	mDifficultyValue.setCaption(toString(difficultyValue));
	mDifficultyBonus.setCaption(toString(difficultyBonus));
	mBaseScoreValue.setCaption(toString(base));
	mBonusScoreValue.setCaption(toString(bonus));
	mTotalScoreValue.setCaption(toString(total));

	// Adjust the sizes.
	mCaption.adjustSize();
	mTimeValue.adjustSize();
	mTimeBonus.adjustSize();
	mMapValue.adjustSize();
	mMapBonus.adjustSize();
	mDifficultyValue.adjustSize();
	mDifficultyBonus.adjustSize();
	mBaseScoreValue.adjustSize();
	mBonusScoreValue.adjustSize();
	mTotalScoreValue.adjustSize();

	// Hide all the appropriate labels.
	mTimeValue.setVisible(false);
	mTimeBonus.setVisible(false);
	mMapValue.setVisible(false);
	mMapBonus.setVisible(false);
	mDifficultyValue.setVisible(false);
	mDifficultyBonus.setVisible(false);
	mBaseScoreValue.setVisible(false);
	mBonusScoreValue.setVisible(false);
	mTotalScoreValue.setVisible(false);
	mMessage.setVisible(false);

	// Adjust the size of the widget.
	adjust();

	// Start the display timer.
	mTimer.start();
}

void LevelCompleteWidget::keyPressed(gcn::KeyEvent& e)
{
	// If this widget has focus, and the space bar was pressed, then signal the widget is completed.
	if(isFocused() && e.getKey().getValue() == gcn::Key::SPACE)
		distributeActionEvent();
}

void LevelCompleteWidget::logic()
{
	// If the timer is started and has enough time has elapsed to display the next set of values, display them and play a sound.
	if(mTimer.isStarted() && mTimer.getTime() >= LEVELCOMPLETEWIDGET_TIMERINTERVAL)
	{
		// If the time hasn't been displayed, display it.
		if(!mTimeValue.isVisible())
		{
			// Display the time information.
			mTimeValue.setVisible(true);
			mTimeBonus.setVisible(true);

			// Play a sound.
//			AudioManager::playSound(LEVEL COMPLETE SOUND, 1);@todo find sound and implement.

			// Reset the timer.
			mTimer.start();
		}
		// If the time hasn't been displayed, display it.
		else if(!mMapValue.isVisible())
		{
			// Display the time information.
			mMapValue.setVisible(true);
			mMapBonus.setVisible(true);

			// Play a sound.
//			AudioManager::playSound(LEVEL COMPLETE SOUND, 1);@todo find sound and implement.

			// Reset the timer.
			mTimer.start();
		}
		// If the time hasn't been displayed, display it.
		else if(!mDifficultyValue.isVisible())
		{
			// Display the time information.
			mDifficultyValue.setVisible(true);
			mDifficultyBonus.setVisible(true);

			// Play a sound.
//			AudioManager::playSound(LEVEL COMPLETE SOUND, 1);@todo find sound and implement.

			// Reset the timer.
			mTimer.start();
		}
		else if(!mBaseScoreValue.isVisible())
		{
			// Display the base, bonus, and total information.
			mBaseScoreValue.setVisible(true);
			mBonusScoreValue.setVisible(true);
			mTotalScoreValue.setVisible(true);

			// Play a sound.
//			AudioManager::playSound(LEVEL COMPLETE SOUND, 1);@todo find sound and implement.

			// Reset the timer.
			mTimer.start();
		}
		else if(!mMessage.isVisible())
		{
			// Display the message.
			mMessage.setVisible(true);

			// First, request focus.  If there's a problem, then error.
			requestFocus();

			// Stop the timer.
			mTimer.stop();
		}
	}

	// Continue logic.
	gcn::Container::logic();
}
