/*
 * GameInterfaceInterface.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */

#include "GameInterfaceInterface.hpp"

#include <stdexcept>

#include "../Engine/Logger.hpp"

using std::invalid_argument;
using std::list;
using std::runtime_error;
using std::string;

void GameInterfaceInterface::mAddCreatureDisplay(Creature* creature)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->addCreatureDisplay(creature);
	}
}

void GameInterfaceInterface::mAddMessage(const string& title, const string& message)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->addMessage(title, message);
	}
}

unsigned int GameInterfaceInterface::mAddTask(const std::string& title, const std::string& message)
{
	if(mInterfaceListener)
	{
		return mInterfaceListener->addTask(title, message);
	}

	Logger::error("Cannot add task.  No interface listener set.");
	return 0;
}

void GameInterfaceInterface::mCompleteTask(unsigned int id)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->completeTask(id);
	}
}

void GameInterfaceInterface::mDisplayMessage(const string& caption, const string& message, const string& sprite, const string& keyword)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->displayMessage(caption, message, sprite, keyword);
	}
}

void GameInterfaceInterface::mFocusViewport(const Entity* entity)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->setViewportFocus(entity);
	}
}

void GameInterfaceInterface::mFocusViewport(int x, int y)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->setViewportFocus(x, y);
	}
}

Vector GameInterfaceInterface::mGetViewportOffset()
{
	if(mInterfaceListener)
	{
		return mInterfaceListener->getViewportOffset();
	}

	Logger::error("Cannot get viewport offset, no interface listener set.");

	return Vector();
}

void GameInterfaceInterface::mRemoveCreatureDisplay(Creature* creature)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->removeCreatureDisplay(creature);
	}
}

void GameInterfaceInterface::mSetViewportBounds(const Rectangle& bounds)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->setViewportBounds(bounds);
	}
}

void GameInterfaceInterface::mSignalLetter()
{
	if(mInterfaceListener)
	{
		mInterfaceListener->signalLetterIndicator();
	}
}

void GameInterfaceInterface::setInterfaceListener(InterfaceListener* listener)
{
	mInterfaceListener = listener;
}

InterfaceListener* GameInterfaceInterface::mInterfaceListener = 0;
