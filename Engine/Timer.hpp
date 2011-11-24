/*
 * Timer.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: alienjon
 */
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <SFML/System.hpp>

/*
 * @brief A class that implements functions for a timer.
 */
class Timer
{
	public:
	/**
	 * @brief The basic constructor initializes a timer's properties.
	 */
	Timer();

	/**
	 * @brief Returns the current time since this timer was started or reset.
	 * @return The time (in seconds) since the timer was started or reset.
	 */
	unsigned int getTime() const;

	/**
	 * @brief Returns the paused state of the timer.
	 * @return True if the timer is paused, false if it unpaused.
	 */
	bool isPaused() const;

	/**
	 * @brief Returns the running state of the timer.
	 * @return True if the timer is running, false if it is stopped.
	 */
	virtual bool isStarted() const;

	/**
	 * @brief Pause the timer.
	 */
	void pause();

	/**
	 * @brief Start the timer.
	 */
	void start();

	/**
	 * @brief Stop the timer.
	 */
	void stop();

	/**
	 * @brief Unpause the timer.
	 */
	void unpause();

	private:
	// The internal clock.
	sf::Clock mClock;

	// The current time.
	unsigned int mCurrentTime;

	// The time the timer was paused.
	unsigned int mPausedTime;

	// True if the timer was running
	bool mRunning;

	// True if the timer is paused.
	bool mPaused;
};

#endif /* TIMER_HPP_ */
