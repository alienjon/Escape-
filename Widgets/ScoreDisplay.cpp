/*
 * ScoreDisplay.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: alienjon
 */
#include "ScoreDisplay.hpp"

#include <string>

#include "../Engine/FontManager.hpp"
#include "../main.hpp"

using std::string;

const unsigned int SCORE_COUNTER_INTERVAL = 25;

ScoreDisplay::ScoreDisplay() :
	mScore(0),
	mCounter(0)
{
	// Load the font.
	mFont = FontManager::getSFFont("Fonts/VeraMono.ttf");

	// Setup the text.
    mScoreText.setFont(mFont);
    mScoreText.setString("Score: 0");
    mScoreText.setCharacterSize(18);
    mScoreText.setColor(sf::Color::Magenta);
    mScoreText.setStyle(sf::Text::Bold);
    mScoreTimer.start();
}

void ScoreDisplay::changeScore(int change)
{
	mCounter += change;
	mScoreText.setString("Score: " + toString(mScore));
}

void ScoreDisplay::draw(sf::RenderWindow& renderer)
{
	renderer.draw(mScoreText);
}

unsigned int ScoreDisplay::getHeight() const
{
	return mScoreText.getCharacterSize();
}

unsigned int ScoreDisplay::getWidth() const
{
	return mScoreText.getLocalBounds().width;
}

void ScoreDisplay::logic()
{
	// Update the score.
	if(mCounter != 0 && mScoreTimer.getTime() >= SCORE_COUNTER_INTERVAL)
	{
		// Only increment the score by 1, but determine the direction.
		int sign = (mCounter != 0) ? mCounter / abs(mCounter) : 0;

		// Increment the score.
		mScore = (sign < 0 && mScore == 0) ? 0 : mScore + sign;

		// Set the score.
		mScoreText.setString("Score: " + toString(mScore));

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}
}

void ScoreDisplay::setPosition(unsigned int x, unsigned int y)
{
	mScoreText.setPosition(x, y);
}
