/*
 * GameOverWidget.cpp
 *
 *  Created on: Aug 6, 2009
 *      Author: alienjon
 */

#include "GameOverWidget.hpp"

#include <cmath>

using namespace std;

GameOverWidget::GameOverWidget() : mMenu("Return to Main Menu", EVENT_MAINMENU),
                                   mQuit("Quit the Game", EVENT_QUIT)
{
    mMenu.addEventListener(this);
    mQuit.addEventListener(this);
    setOpaque(false);

    add(&mMenu);
    add(&mQuit);

    mAdjustSize();
}

GameOverWidget::~GameOverWidget()
{
    // Remove the listeners.
    mMenu.removeEventListener(this);
    mQuit.removeEventListener(this);
}

void GameOverWidget::mAdjustSize()
{
	mMessage.setSize(getWidth(), mMessage.getHeight()); // @todo Adjust the size of the message text.
	mMessage.setPosition((getWidth() / 2) - (mMessage.getWidth() / 2), 0);
	mMenu.setPosition((getWidth() / 2) - (mMenu.getWidth() / 2), mMessage.getY() + mMessage.getHeight() + 10);
	mQuit.setPosition((getWidth() / 2) - (mQuit.getWidth() / 2), mMenu.getY() + mMenu.getHeight() + 10);
}

void GameOverWidget::addEventListener(EventListener* listener)
{
    mEventListeners.push_back(listener);
}

void GameOverWidget::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    for(list<EventListener*>::iterator it = mEventListeners.begin(); it != mEventListeners.end(); ++it)
    {
        (*it)->eventOccurred(event, content, creatureMovedToPointListener);
    }
}

void GameOverWidget::removeEventListener(EventListener* listener)
{
    mEventListeners.push_back(listener);
}

void GameOverWidget::setMessage(const string& message)
{
	mMessage.setText(message);
	mAdjustSize();
}
