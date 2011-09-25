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

void GameInterfaceInterface::mSetViewportBounds(const Rectangle& bounds)
{
	if(mInterfaceListener)
	{
		mInterfaceListener->setViewportBounds(bounds);
	}
}

void GameInterfaceInterface::setInterfaceListener(InterfaceListener* listener)
{
	mInterfaceListener = listener;
}

InterfaceListener* GameInterfaceInterface::mInterfaceListener = 0;
