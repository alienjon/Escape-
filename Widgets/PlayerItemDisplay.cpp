/*
 * PlayerItemDisplay.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: alienjon
 */
#include "PlayerItemDisplay.hpp"

#include "../Engine/Colors.hpp"
#include "../Entities/Item.hpp"
#include "../Engine/VideoManager.hpp"

PlayerItemDisplay::PlayerItemDisplay() :
	mFirstItem(0),
	mSecondItem(0),
	mThirdItem(0),
	mLeft(false),
	mRight(false)
{
	// Configure the widget.
	setSize(150, 50);
	addKeyListener(this);
	setFocusable(true);
	setOpaque(false);

	// Add the icons.
	add(&mFirst, 1, 1);
	add(&mSecond, 51, 1);
	add(&mThird, 101, 1);
}

void PlayerItemDisplay::draw(gcn::Graphics* graphics)
{
	// Draw the rest of the display.
	gcn::Container::draw(graphics);

	// Draw the selection box on top.
	if(isModalFocused())
	{
		graphics->setColor(gcn::Color(255, 0, 0));
		if(mLeft && !mRight)
		{
			graphics->drawRectangle(gcn::Rectangle(0, 0, 50, 50));
			graphics->drawRectangle(gcn::Rectangle(1, 1, 48, 48));
		}
		else if(!mLeft && mRight)
		{
			graphics->drawRectangle(gcn::Rectangle(100, 0, 50, 50));
			graphics->drawRectangle(gcn::Rectangle(101, 1, 48, 48));
		}
		else
		{
			graphics->drawRectangle(gcn::Rectangle(50, 0, 50, 50));
			graphics->drawRectangle(gcn::Rectangle(51, 1, 48, 48));
		}
	}
}

bool PlayerItemDisplay::itemPickedUp(Item& item)
{
	if(!mSecondItem)
	{
		mSecondItem = &item;
		mSecond.setImage(gcn::Image::load(mSecondItem->getImageFilename()));
		return true;
	}
	else if(!mFirstItem)
	{
		mFirstItem = &item;
		mFirst.setImage(gcn::Image::load(mFirstItem->getImageFilename()));
		return true;
	}
	else if(!mThirdItem)
	{
		mThirdItem = &item;
		mThird.setImage(gcn::Image::load(mThirdItem->getImageFilename()));
		return true;
	}
	else
		return false;

}

void PlayerItemDisplay::keyPressed(gcn::KeyEvent& event)
{
	// Only do input if this widget has modal focus.
	if(isModalFocused())
	{
		if(event.getKey().getValue() == gcn::Key::LEFT)
			mLeft = true;
		if(event.getKey().getValue() == gcn::Key::RIGHT)
			mRight = true;
		if(event.getKey().getValue() == gcn::Key::SPACE)
		{
			if(mLeft && !mRight && mFirstItem)
			{
				mFirstItem->use();
				mFirstItem = 0;
				mFirst.setImage(0);
			}
			else if(!mLeft && mRight && mThirdItem)
			{
				mThirdItem->use();
				mThirdItem = 0;
				mThird.setImage(0);
			}
			else if(mSecondItem)
			{
				mSecondItem->use();
				mSecondItem = 0;
				mSecond.setImage(0);
			}
		}
	}
}

void PlayerItemDisplay::keyReleased(gcn::KeyEvent& event)
{
	// If the shift key is pressed, give the item display widget full access.
	if(event.getKey().getValue() == gcn::Key::LEFT_SHIFT || event.getKey().getValue() == gcn::Key::RIGHT_SHIFT)
	{
		releaseModalFocus();
		mLeft = mRight = false;
	}

	// Only do input if this widget has modal focus.
	if(isModalFocused())
	{
		if(event.getKey().getValue() == gcn::Key::LEFT)
			mLeft = false;
		if(event.getKey().getValue() == gcn::Key::RIGHT)
			mRight = false;
	}
}
