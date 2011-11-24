/*
 * FPSDisplayWidget.cpp
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */
#include "FPSDisplayWidget.hpp"

#include "../Engine/FontManager.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

FPSDisplayWidget::FPSDisplayWidget() : gcn::Label(),
	mCounter(0)
{
	// Start the timer.
	mTimer.start();

	// Set the font.
	setFont(FontManager::getGCNFont(FONT_DEFAULT));
}

void FPSDisplayWidget::logic()
{
	// Another frame was called.
	mCounter++;

	// Perform GCN logic.
	gcn::Label::logic();

	// Calculate the FPS.
	if(mTimer.getTime() >= 1000)
	{
		// Update the FPS.
		setCaption(toString(mCounter));
		adjustSize();

		// Reset the FPS timer value.
		mTimer.start();
		mCounter = 0;
	}
}
