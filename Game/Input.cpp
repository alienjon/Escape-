/*
 * Input.cpp
 *
 *  Created on: Mar 23, 2010
 *      Author: alienjon
 */

#include "Input.hpp"

#include <string>

#include "../Game/GUI.hpp"
#include "../Engine/Logger.hpp"

using std::set;
using std::string;

Input::Input()
{
	clear();
}

Input::~Input()
{
}

void Input::clear()
{
	mKeys.clear();
	mPreviousKeys.clear();
	mMouseButtons.clear();
	mMousePosition.x = 0;
	mMousePosition.y = 0;
	mAlt = mCaps = mControl = mMeta = mShift = false;
}

void Input::displayInputState() const
{
	// Generate a string of the currently pressed keys.
	string keys,
		   modifier = (mAlt) ? "ALT" : "" + (mCaps) ? " CAPS" : "" + (mControl) ? " CTRL" : "" +
					  (mMeta) ? " META" : "" + (mShift) ? " SHIFT" : "";
	for(set<SDLKey>::const_iterator it = mKeys.begin(); it != mKeys.end(); ++it)
	{
		keys += SDL_GetKeyName(*it) + ' ';
	}
	Logger::log("Displaying Input State");
	Logger::log("----------------------");
	Logger::log("Keys Currently Pressed: " + keys);

	Logger::log("----------------------");
}

const Vector& Input::getMousePosition() const
{
	return mMousePosition;
}

const int Input::getMouseX() const
{
	return mMousePosition.x;
}

const int Input::getMouseY() const
{
	return mMousePosition.y;
}

void Input::handleInput(GUI* gui)
{
	// Update the previous keys before setting the new states.
	mPreviousKeys = mKeys;

    while(SDL_PollEvent(&mEvent))
    {
		switch(mEvent.type)
		{
			case SDL_KEYDOWN:
			{
				setKeyPressed(mEvent.key.keysym.sym, true);
				break;
			}
			case SDL_KEYUP:
			{
				setKeyPressed(mEvent.key.keysym.sym, false);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				setMousePressed(mEvent.button.button, true);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				setMousePressed(mEvent.button.button, false);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				setMousePosition(mEvent.button.x, mEvent.button.y);
				break;
			}
//			case SDL_QUIT: @todo I'm leaving this alone for now.  Should hard-quitting like this even exist for this type of game?
//			{
//				mIsRunning = false;
//				break;
//			}
			default:
			{}
		}

        // Handle GUIchan input.
        gui->pushInput(mEvent);
    }
}

bool Input::isAltPressed() const
{
	return mAlt;
}

bool Input::isCapslockPressed() const
{
	return mCaps;
}

bool Input::isControlPressed() const
{
	return mControl;
}

bool Input::isKeyClicked(SDLKey key) const
{
	return !isKeyPressed(key) && mPreviousKeys.find(key) != mPreviousKeys.end();
}

bool Input::isKeyPressed(SDLKey key) const
{
	return mKeys.find(key) != mKeys.end();
}

bool Input::isMetaPressed() const
{
	return mMeta;
}

bool Input::isMousePressed(Uint8 button) const
{
	return mMouseButtons.find(button) != mMouseButtons.end();
}

bool Input::isShiftPressed() const
{
	return mShift;
}

void Input::setKeyPressed(SDLKey key, bool pressed)
{
	switch(key)
	{
		case SDLK_LALT     : mAlt = pressed; break;
		case SDLK_RALT     : mAlt = pressed; break;
		case SDLK_CAPSLOCK : mCaps = pressed; break;
		case SDLK_LCTRL    : mControl = pressed; break;
		case SDLK_RCTRL	   : mControl = pressed; break;
		case SDLK_LMETA    : mMeta = pressed; break;
		case SDLK_RMETA	   : mMeta = pressed; break;
		case SDLK_LSHIFT   : mShift = pressed; break;
		case SDLK_RSHIFT   : mShift = pressed; break;
		default:
		{
			if(pressed)
			{
				mKeys.insert(key);
			}
			else
			{
				mKeys.erase(key);
			}
		}
	}
}

void Input::setMousePosition(int x, int y)
{
	mMousePosition.x = x;
	mMousePosition.y = y;
}

void Input::setMousePressed(Uint8 button, bool pressed)
{
	if(pressed)
	{
		mMouseButtons.insert(button);
	}
	else
	{
		mMouseButtons.erase(button);
	}
}
