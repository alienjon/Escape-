/*
 * TimerWidget.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#ifndef TIMERWIDGET_HPP_
#define TIMERWIDGET_HPP_

#include "../guichan.hpp"
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
	 * @brief Perform logic.
	 */
	virtual void logic();

	/**
	 * @brief Pause the timer.
	 */
	virtual void pause();

	/**
	 * @brief Start the timer.
	 */
	virtual void start();

	/**
	 * @brief Stop the timer.
	 */
	virtual void stop();

	protected:
	// The timer.
	Timer mTimer;
};

#endif /* TIMERWIDGET_HPP_ */
