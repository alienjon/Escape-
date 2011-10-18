/*
 * LevelCompleteWidget.h
 *
 *  Created on: Oct 11, 2011
 *      Author: alienjon
 */
#ifndef LEVELCOMPLETEWIDGET_H_
#define LEVELCOMPLETEWIDGET_H_

#include <string>

#include "../guichan.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A widget to display the final score at the end of the level.
 * @todo Implement showing the number of zombies killed, innocents saved?
 */
class LevelCompleteWidget : public gcn::Container, public gcn::KeyListener
{
	public:
	/**
	 * @brief Default constructor.
	 */
	LevelCompleteWidget();
	virtual ~LevelCompleteWidget();

	/**
	 * @brief Adjust the sizes and positions of the internal widgets.
	 * @note This will not adjust the size of the widget.
	 */
	virtual void adjust();

	/**
	 * @brief Display the widget and start displaying the level results.
	 * @param timeValue The time raw score.
	 * @param timeBonus The bonus from the time.
	 * @param mapValue The map difficulty's raw score.
	 * @param mapBonus The bonus from the map difficulty.
	 * @param difficultyValue The raw score from the game difficulty.
	 * @param difficultyBonus The bonus score from the game difficulty.
	 * @param base The base score.
	 * @param bonus The bonus score from the base score.
	 * @param total The total score.
	 */
	virtual void display(unsigned int timeValue, unsigned int timeBonus, unsigned int mapValue, unsigned int mapBonus,
						 unsigned int difficultyValue, double difficultyBonus, unsigned int base, unsigned int bonus, unsigned int total);

	/**
	 * @brief Handle key pressed to check to close the widget.
	 * @param event The key event.
	 */
	virtual void keyPressed(gcn::KeyEvent& e);

	/**
	 * @brief Perform logic.
	 */
	virtual void logic();

	private:
	// Display timer.
	Timer mTimer;

	// The internal widgets.
	/*
	 * @todo Maybe have a different label for the 'actual' label, one for the value for that label, and one for the bonus that attribute provides.
	 * ie:Value			Value	Bonus
	 * Time Completed:	1:24:43	300		<- The time completed (not sure how to compute score based on time...)
	 * Map Complexity:	400		400		<- This is simply the dimension of the map (width * height) and the bonus is equal to the value.
	 * Difficulty:		15		x1.5	<- This is the difficulty of the game.  The bonus is difficulty/10.
	 *
	 * Base Score:		1450			<- The score before adding the bonus (this would include 'immediate points' for killing zombies, setting traps, getting stuff, saving people, etc...).
	 * Bonus Score:		1050			<- This is the bonus score calculated by adding all of the bonus scores together and multiplying it by the difficulty modifier (in this case: (300+400)*1.5=1050
	 * Total Score:		2500			<- This is the total score, equal to the previous score plus the bonus score.
	 *
	 * press space to continue			<- This is a message to the player to press space to continue.
	 */
	gcn::Label mCaption,
			   mTimeLabel,		 mTimeValue,	   mTimeBonus,
			   mMapLabel,		 mMapValue,		   mMapBonus,
			   mDifficultyLabel, mDifficultyValue, mDifficultyBonus,
			   mBaseScoreLabel,  mBaseScoreValue,
			   mBonusScoreLabel, mBonusScoreValue,
			   mTotalScoreLabel, mTotalScoreValue,
			   mMessage;

};

#endif /* LEVELCOMPLETEWIDGET_H_ */
