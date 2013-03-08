/*
 * TimerWidget.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#ifndef TIMERWIDGET_HPP_
#define TIMERWIDGET_HPP_

#include <list>

#include <SFML/Graphics.hpp>

#include "../Listeners/TimeChangeListener.hpp"
#include "../Engine/Timer.hpp"
#include "../Listeners/TimeUpListener.hpp"

/**
 * @brief A widget that displays a counting timer.  For a timer to count down
 * a time, @see CountdownTimerWidget
 */
class TimerWidget : public TimeChangeListener
{
	public:
	/**
	 * @brief Default constructor.
	 */
	TimerWidget();

	/**
	 * @brief Add a time up listener.
	 * @param listener The listener to add.
	 */
	void addTimeUpListener(TimeUpListener* listener);

	/**
	 * @brief Distribute that the timer ran out to the listeners.
	 */
	void distributeTimeUp();

	/**
	 * @brief Draw the widget onto the renderer.
	 * @param renderer The renderer on which to draw.
	 */
	virtual void draw(sf::RenderWindow& renderer);

	/**
	 * @brief Get the height of the widget.
	 * @return The height of the widget.
	 */
	int getHeight() const;

	/**
	 * @brief Get the current timer's time.
	 * @return The timer's current time.
	 */
	virtual unsigned int getTime() const;

	/**
	 * @brief Get the width of the widget.
	 * @return The width.
	 */
	int getWidth() const;

	/**
	 * @brief Perform logic.
	 */
	virtual void logic();

	/**
	 * @brief Pause the timer.
	 */
	virtual void pause();

	/**
	 * @brief Remove a time up listener.
	 * @param listener The listener to remove.
	 */
	void removeTimeUpListener(TimeUpListener* listener);

	/**
	 * @brief Set the position of the widget.
	 * @param x The x location.
	 * @param y The y location.
	 */
	void setPosition(int x, int y);

	/**
	 * @brief Start the timer.
	 * @param startTime The time the counter will start counting down from.
	 * @note If a number less than zero is provided (or the parameter is left empty) the timer will start counting up from zero.
	 * @note If a value is provided as a paremeter the timer will count from that time (in seconds) to zero and stop.
	 */
	virtual void start(unsigned int startTime = 0);

	/**
	 * @brief Stop the timer.
	 */
	virtual void stop();

	/**
	 * @brief Change the time.
	 * @param time The amount to change the time.
	 */
	virtual void timeChange(int time);

	/**
	 * @brief Unpause the timer.
	 */
	virtual void unpause();

	protected:
	// The timer.
	Timer mTimer;

	// The start time.
	unsigned int mStartTime;

	// The display.
	sf::Font mFont;
	sf::Text mText;

	// The time up listeners.
	std::list<TimeUpListener*> mTimeUpListeners;
};

#endif /* TIMERWIDGET_HPP_ */
