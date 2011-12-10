/*
 * PlayerItemDisplay.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: alienjon
 */
#ifndef PLAYERITEMDISPLAY_HPP_
#define PLAYERITEMDISPLAY_HPP_

#include <SFML/Graphics.hpp>

#include "../Engine/guichan.hpp"
#include "../Listeners/PickupListener.hpp"

class Item;
class Player;

/**
 * @brief The player item display shows the 3 items the player has picked up.
 */
class PlayerItemDisplay : public gcn::Container, public gcn::KeyListener, public PickupListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param player The player.
	 */
	PlayerItemDisplay(Player& player);

	/**
	 * @brief Draw the widget.
	 * @param graphics The graphics object with which to draw.
	 */
	virtual void draw(gcn::Graphics* graphics);

	/**
	 * @brief An item was picked up by the player.
	 * @param item The picked up item.
	 * @return True if the item was picked up.
	 */
	virtual bool itemPickedUp(Item& item);

	/**
	 * @brief A key was pressed.
	 * @param event The key event.
	 */
	void keyPressed(gcn::KeyEvent& event);

	/**
	 * @brief A key was released.
	 * @param event The key event.
	 */
	void keyReleased(gcn::KeyEvent& event);

	private:
	// The three items.
	gcn::Icon mFirst, mSecond, mThird;

	// The 3 held items.
	Item *mFirstItem, *mSecondItem, *mThirdItem;

	// The state of the left/right button pressed.
	bool mLeft, mRight;

	// The player.
	Player& mPlayer;
};

#endif /* PLAYERITEMDISPLAY_HPP_ */
