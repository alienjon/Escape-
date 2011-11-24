///*
// * GameScreenMenuBar.hpp
// *
// *  Created on: Oct 2, 2011
// *      Author: alienjon
// */
//#ifndef GAMESCREENMENUBAR_HPP_
//#define GAMESCREENMENUBAR_HPP_
//
//#include "../guichan.hpp"
//#include "../Widgets/TimerWidget.hpp"
//
//class Entity;
//
///**
// * @brief The bar at the top of the screen.
// */
//class GameScreenMenuBar : public gcn::Container
//{
//	public:
//	/**
//	 * @brief Constructor.
//	 */
//	GameScreenMenuBar();
//
//	/**
//	 * @brief Adjust internal positions/sizings.
//	 * @note This should be called after a size change occurs for this widget.
//	 */
//	virtual void adjustInternals();
//
//	/**
//	 * @brief Get the current level time.
//	 * @return The game time as a value.
//	 */
//	virtual float getTime() const;
//
//	/**
//	 * @brief Pause the timer.
//	 */
//	virtual void pause();
//
//	/**
//	 * @brief Set the score to display.
//	 * @param score The score to set.
//	 */
//	virtual void setScore(unsigned int score);
//
//	/**
//	 * @brief Start the timer.
//	 * @param startTime The time the counter will start counting down from.
//	 * @note If a number less than zero is provided (or the parameter is left empty) the timer will start counting up from zero.
//	 * @note If a value is provided as a paremeter the timer will count from that time (in seconds) to zero and stop.
//	 */
//	virtual void start(float startTime = -1);
//
//	/**
//	 * @brief Stop the timer.
//	 */
//	virtual void stop();
//
//	/**
//	 * @brief Unpause the timer.
//	 */
//	virtual void unpause();
//
//	private:
//	// The timer widget.
//	TimerWidget mTimerWidget;
//
//	// Score stuff.
//	gcn::Container mScore;
//	gcn::Label mScoreLabel, mScoreValue;
//};
//
//#endif /* GAMESCREENMENUBAR_HPP_ */
