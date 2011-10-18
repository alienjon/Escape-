/*
 * GameScreenMenuBar.hpp
 *
 *  Created on: Oct 2, 2011
 *      Author: alienjon
 */
#ifndef GAMESCREENMENUBAR_HPP_
#define GAMESCREENMENUBAR_HPP_

#include "../guichan.hpp"
#include "../Widgets/MiniMap.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Surface.hpp"
#include "../Widgets/TimerWidget.hpp"

class Entity;

/**
 * @brief The bar at the top of the screen.
 */
class GameScreenMenuBar: public gcn::Container
{
	public:
	/**
	 * @brief Constructor.
	 */
	GameScreenMenuBar();

	/**
	 * @brief Adjust internal positions/sizings.
	 * @note This should be called after a size change occurs for this widget.
	 */
	virtual void adjustInternals();

	/**
	 * @brief Configure the mini map.
	 * @param map The map image to set.
	 * @param entity The entity to focus the camera upon.
	 */
	virtual void configureMiniMap(Surface* map, Entity* entity);

	/**
	 * @brief Get the current level time.
	 * @return The game time as a value.
	 */
	virtual unsigned int getTime() const;

	/**
	 * @brief Pause the timer.
	 */
	virtual void pause();

	/**
	 * @brief Set the score to display.
	 * @param score The score to set.
	 */
	virtual void setScore(unsigned int score);

	/**
	 * @brief Start the timer.
	 */
	virtual void start();

	/**
	 * @brief Stop the timer.
	 */
	virtual void stop();

	private:
	// The timer widget.
	TimerWidget mTimerWidget;

	// Score stuff.
	gcn::Container mScore;
	gcn::Label mScoreLabel, mScoreValue;
	MiniMap mMiniMap;
};

#endif /* GAMESCREENMENUBAR_HPP_ */
