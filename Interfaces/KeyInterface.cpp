/*
 * KeyInterface.cpp
 *
 *  Created on: Feb 16, 2013
 *      Author: alienjon
 */
#include "KeyInterface.hpp"

using std::list;

KeyInterface::KeyInterface()
{
}

KeyInterface::~KeyInterface()
{
}

void KeyInterface::addKeyListener(KeyListener* listener)
{
	mKeyListeners.push_back(listener);
}

void KeyInterface::distributeKeyPressed(const sf::Event& event)
{
	for(list<KeyListener*>::const_iterator it(mKeyListeners.begin()); it != mKeyListeners.end(); ++it)
		(*it)->keyPressed(event);
}

void KeyInterface::distributeKeyReleased(const sf::Event& event)
{
	for(list<KeyListener*>::const_iterator it(mKeyListeners.begin()); it != mKeyListeners.end(); ++it)
		(*it)->keyReleased(event);
}

void KeyInterface::removeKeyListener(KeyListener* listener)
{
	mKeyListeners.remove(listener);
}
