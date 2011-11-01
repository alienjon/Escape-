/*
 * GameScreenMenuBar.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#include "GameScreenMenuBar.hpp"

#include "../Engine/Colors.hpp"
#include "../Entities/Entity.hpp"
#include "../Managers/FontManager.hpp"
#include "../main.hpp"

GameScreenMenuBar::GameScreenMenuBar()
{
	// Configure the widget.
	setBaseColor(COLOR_WHITE);
	add(&mTimerWidget);
	mScoreLabel.setFont(FontManager::get(FONT_CAPTION));
	mScoreLabel.setCaption("Score:");
	mScoreLabel.adjustSize();
	mScoreValue.setFont(FontManager::get(FONT_DEFAULT));
	mScoreValue.setCaption("0");
	mScoreValue.adjustSize();
	mScore.add(&mScoreLabel, 0, 0);
	mScore.add(&mScoreValue, mScoreLabel.getWidth(), 0);
	mScore.setOpaque(false);
	mScore.setSize(mScoreLabel.getWidth() + 4 + mScoreValue.getWidth(), mScoreLabel.getHeight() > mScoreValue.getHeight() ? mScoreLabel.getHeight() : mScoreValue.getHeight());
	add(&mScore);
	add(&mMiniMap);

	// Adjust the positions.
	adjustInternals();
}

void GameScreenMenuBar::adjustInternals()
{
    mTimerWidget.setPosition(0, (getHeight() / 2) - (mTimerWidget.getHeight() / 2));
    mMiniMap.setSize(getWidth() * 0.33, getHeight() * 0.90);
    mMiniMap.setPosition((getWidth() / 2) - (mMiniMap.getWidth() / 2), (getHeight() / 2) - (mMiniMap.getHeight() / 2));
    mScore.setPosition(mMiniMap.getX() + mMiniMap.getWidth(), (getHeight() / 2) - (mScore.getHeight() / 2));
    mScore.setWidth(getWidth() - mScore.getX());
}

void GameScreenMenuBar::configureMiniMap(Surface* map, Entity* entity)
{
	mMiniMap.setMap(map);
	mMiniMap.center(entity);
}

unsigned int GameScreenMenuBar::getTime() const
{
	return mTimerWidget.getTime();
}

void GameScreenMenuBar::pause()
{
	mTimerWidget.pause();
}

void GameScreenMenuBar::setScore(unsigned int score)
{
	mScoreValue.setCaption(toString(score));
	mScoreValue.adjustSize();
}

void GameScreenMenuBar::start(int startTime)
{
	mTimerWidget.start(startTime);
}

void GameScreenMenuBar::stop()
{
	mTimerWidget.stop();
}

void GameScreenMenuBar::unpause()
{
	mTimerWidget.unpause();
}
