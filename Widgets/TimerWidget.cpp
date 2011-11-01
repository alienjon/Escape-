/*
 * TimerWidget.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#include "TimerWidget.hpp"

#include "../Game/Game.hpp"
#include "../Managers/FontManager.hpp"
#include "../main.hpp"

using std::string;

TimerWidget::TimerWidget() :
	mStartTime(0)
{
	// Set the font.
	setFont(FontManager::get(FONT_DEFAULT));//@todo find a timer widget font
}

unsigned int TimerWidget::getTime() const
{
	return (mStartTime < 0) ? mTimer.getTime() : (unsigned int)mStartTime - mTimer.getTime();
}

void TimerWidget::logic()
{
	// Perform GCN logic.
	gcn::Label::logic();

	// Update the counter if the timer is running.
	if(mTimer.isStarted() && !mTimer.isPaused())
	{
		// If the timer has exceeded the start time, then time is up.
		if(mStartTime >= 0 && mTimer.getTime() > (unsigned int)mStartTime)
			stop();
		setCaption(convertToTime((mStartTime < 0) ? mTimer.getTime() : (unsigned int)mStartTime - mTimer.getTime()));
		adjustSize();
	}
}

void TimerWidget::pause()
{
	mTimer.pause();
}

void TimerWidget::start(int startTime)
{
	mStartTime = startTime;
	mTimer.start();
}

void TimerWidget::stop()
{
	mStartTime = -1;
	mTimer.stop();
}

void TimerWidget::unpause()
{
	mTimer.unpause();
}
