/*
 * TimerWidget.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#include "TimerWidget.hpp"

#include "../Game/Game.hpp"
#include "../Engine/FontManager.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

using std::string;

TimerWidget::TimerWidget() :
	mStartTime(0)
{
	// Set the font.
	setFont(FontManager::getGCNFont(FONT_DEFAULT));

	// Set default size.
	setCaption("000:00:00");
	adjustSize();
	setAlignment(gcn::Graphics::LEFT);//@fixme This isn't actually aligning left.
}

unsigned int TimerWidget::getTime() const
{
	return (mStartTime == 0) ? mTimer.getTime() : mTimer.getTime() - mStartTime;
}

void TimerWidget::logic()
{
	// Perform GCN logic.
	gcn::Label::logic();

	// If the timer has exceeded the start time, then time is up.
	if(mStartTime > 0 && mTimer.getTime() >= mStartTime)
		stop();
	setCaption(convertToTime((mStartTime == 0) ? mTimer.getTime() : mStartTime - mTimer.getTime()));
	adjustSize();
}

void TimerWidget::pause()
{
	mTimer.pause();
}

void TimerWidget::start(unsigned int startTime)
{
	mTimer.start();
	mStartTime = mTimer.getTime() + startTime;
}

void TimerWidget::stop()
{
	mStartTime = 0;
	mTimer.stop();
}

void TimerWidget::timeChange(int time)
{
	if(time < 0 && int(mStartTime) - time < 0)
		stop();
	else
		mStartTime -= time;
}

void TimerWidget::unpause()
{
	mTimer.unpause();
}
