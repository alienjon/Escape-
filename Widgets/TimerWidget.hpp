/*
 * TimerWidget.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#ifndef TIMERWIDGET_HPP_
#define TIMERWIDGET_HPP_

#include "../Engine/guichan.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A widget that displays a counting timer.  For a timer to count down
 * a time, @see CountdownTimerWidget
 */
class TimerWidget : public gcn::Label
{
	public:
	/**
	 * @brief Default constructor.
	 */
	TimerWidget();

	/**
	 * @brief Get the current timer's time.
	 * @return The timer's current time.
	 */
	virtual unsigned int getTime() const;

	/**
	 * @brief Perform logic.
	 */
	virtual void logic();

	/**
	 * @brief Pause the timer.
	 */
	virtual void pause();

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
	 * @brief Unpause the timer.
	 */
	virtual void unpause();

	protected:
	// The timer.
	Timer mTimer;

	// The start time.
	unsigned int mStartTime;
};

#endif /* TIMERWIDGET_HPP_ */
