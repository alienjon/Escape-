#ifndef TIMER_HPP
#define TIMER_HPP

typedef unsigned int uint;

/**
 * @brief A basic timer class that utilizes SDL to keep track of time.
 *
 * Upon construction a timer is not running.  Each method is rather self-explanatory.
 * @see getTime() Will get the current time on the timer.  A zero likely means the timer
 * has not yet been started (@see start())
 */
class Timer
{
	public:
	/**
	 * @brief The basic constructor initializes a timer's properties.
	 */
	Timer();

	/**
	 * @brief Start the timer.
	 */
	void start();

	/**
	 * @brief Stop the timer.
	 */
	void stop();

	/**
	 * @brief Pause the timer.
	 */
	void pause();

	/**
	 * @brief Unpause the timer.
	 */
	void unpause();

	/**
	 * @brief Returns the running state of the timer.
	 * @return True if the timer is running, false if it is stopped.
	 */
	virtual bool isStarted() const;

	/**
	 * @brief Returns the paused state of the timer.
	 * @return True if the timer is paused, false if it unpaused.
	 */
	bool isPaused() const;

	/**
	 * @brief Returns the current time since this timer was started or reset.
	 * @return The time (in milliseconds) since the timer was started or reset.
	 */
	uint getTime();

	private:
	/**
	 * The current time.
	 */
	uint mCurrentTime;

	/**
	 * The time the timer was paused.
	 */
	uint mPausedTime;

	/**
	 * True if the timer was running.
	 */
	bool mRunning;

	/**
	 * True if the timer is paused.
	 */
	bool mPaused;
};

#endif
