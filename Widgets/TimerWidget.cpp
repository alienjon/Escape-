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

TimerWidget::TimerWidget()
{
	// Set the font.
	setFont(FontManager::get(FONT_DEFAULT));//@todo identify a timer widget font
}

void TimerWidget::logic()
{
	// Perform GCN logic.
	gcn::Label::logic();

	// Update the counter.
	setCaption(convertToTime(mTimer.getTime()));
	adjustSize();
}

void TimerWidget::pause()
{
	mTimer.pause();
}

void TimerWidget::start()
{
	mTimer.start();
}

void TimerWidget::stop()
{
	mTimer.stop();
}
