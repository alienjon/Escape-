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
#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::string;

TimerWidget::TimerWidget() :
	mStartTime(0)
{
	// Set the font.
	if(!mFont.loadFromFile("Fonts/VeraMono.ttf"))
		ERROR("TimerWidget::TimerWidget() -> Unable to load font.");
	mText.setFont(mFont);

	// Set defaults
    mText.setCharacterSize(18);
    mText.setColor(sf::Color::Magenta);
    mText.setStyle(sf::Text::Bold);
	mText.setString("000:00:00");
}

void TimerWidget::draw(sf::RenderWindow& renderer)
{
	renderer.draw(mText);
}

int TimerWidget::getHeight() const
{
	return mText.getLocalBounds().height;
}

unsigned int TimerWidget::getTime() const
{
	return (mStartTime == 0) ? mTimer.getTime() : mTimer.getTime() - mStartTime;
}

int TimerWidget::getWidth() const
{
	return mText.getLocalBounds().width;
}

void TimerWidget::logic()
{
	// If the timer has exceeded the start time, then time is up.
	if(mStartTime > 0 && mTimer.getTime() >= mStartTime)
		stop();
	mText.setString(convertToTime((mStartTime == 0) ? mTimer.getTime() : mStartTime - mTimer.getTime()));
}

void TimerWidget::pause()
{
	mTimer.pause();
}

void TimerWidget::setPosition(int x, int y)
{
	mText.setPosition(x, y);
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
