/*
 * FPSDisplayWidget.cpp
 *
 *  Created on: Mar 30, 2009
 *      Author: alienjon
 */

#include "FPSDisplayWidget.hpp"

#include "../Game/Game.hpp"
#include "../Managers/FontManager.hpp"

FPSDisplayWidget::FPSDisplayWidget() : gcn::Label()
{
	// Start the timer.
	mFPSTimer.start();

	// Set the font.
	setFont(FontManager::get(FONT_DEFAULT));
}

FPSDisplayWidget::~FPSDisplayWidget()
{
}

void FPSDisplayWidget::logic()
{
	// Perform GCN logic.
	gcn::Label::logic();

	// Calculate the FPS.
	if(mFPSTimer.getTime() > 1000)
	{
		// Update the FPS.
		setCaption(toString(gFPSCounter));
		adjustSize();

		// Reset the FPS timer value.
		mFPSTimer.start();
		gFPSCounter = 0;
	}
}
