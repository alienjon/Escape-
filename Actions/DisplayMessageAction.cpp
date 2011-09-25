/*
 * DisplayMessageAction.cpp
 *
 *  Created on: May 24, 2010
 *      Author: the-saint
 */
#include "DisplayMessageAction.hpp"

#include <stdexcept>

using std::runtime_error;
using std::string;

DisplayMessageAction::DisplayMessageAction(const string& caption, const string& message, const string& sprite, GameScreen* screen) :
	mCaption(caption),
	mMessage(message),
	mImage(sprite),
	mScreen(screen)
{
	// Only need to check the interface.
	if(!mScreen)
	{
		throw runtime_error("DisplayMessageAction() -> Null interface provided.");
	}
}

DisplayMessageAction::~DisplayMessageAction()
{
}

//void DisplayMessageAction::activate(EnvironmentData& eData)@todo review
//{
//	// Display the message.
//	mScreen->displayMessage(mCaption, mMessage, mImage, "");
//
//	// Done.
//	mPerformed = true;
//}
