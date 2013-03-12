/*
 * ScoreDisplay.hpp
 *
 *  Created on: Mar 7, 2013
 *      Author: alienjon
 */
#ifndef SCOREDISPLAY_HPP_
#define SCOREDISPLAY_HPP_

#include <SFML/Graphics.hpp>

#include "../Listeners/ChangeScoreListener.hpp"
#include "../Engine/Timer.hpp"

/*
 * @brief Display for the current score.
 */
class ScoreDisplay : public ChangeScoreListener
{
	public:
	/**
	 * @brief Default constructor.
	 */
	ScoreDisplay();

	/**
	 * @brief Change the score.
	 * @param change The score change.
	 */
	void changeScore(int change);

	/**
	 * @brief Draw the widget onto the renderer.
	 * @param renderer The renderer on which to draw.
	 */
	void draw(sf::RenderWindow& renderer);

	/**
	 * @brief Get the remaining counter score.
	 * @return The remaining counter score.
	 */
	int getCounter() const;

	/**
	 * @brief Get the height of the widget.
	 * @return The height.
	 */
	unsigned int getHeight() const;

	/**
	 * @brief Get the width of the widget.
	 * @return The width.
	 */
	unsigned int getWidth() const;

	/**
	 * @brief Get the current score.
	 * @return The current score.
	 */
	unsigned int getScore() const;

	/**
	 * @brief Perform widget logic.
	 */
	void logic();

	/**
	 * @brief Set the position of the widget.
	 * @param x The X position.
	 * @param y The Y position.
	 */
	void setPosition(unsigned int x, unsigned int y);

	/**
	 * @brief Set the score.
	 * @param score The score to set to.
	 */
	void setScore(unsigned int score);

	private:
	// This is the score.
	unsigned int mScore;

	// This is the amount to add to the score.
	int mCounter;

	// The score display.
    sf::Text mScoreText;

    // The score timer.
    Timer mScoreTimer;

    // The font.
    sf::Font mFont;
};

#endif /* SCOREDISPLAY_HPP_ */
