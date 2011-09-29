/*
 * Event.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: alienjon
 */

#ifndef EVENT_HPP_
#define EVENT_HPP_

/**
 * @brief Various events that can occur.
 */
enum Event
{
	EVENT_ADDCREDITSCREEN,		// Push a credit screen to the screen queue.
	EVENT_PAUSE,				// Pause the game.
	EVENT_UNPAUSE,				// Unpause the game.
    EVENT_SLIDE_MAINMENU,   	// Slide to the main menu.
    EVENT_SLIDE_NEWMENU,    	// Slide to the new menu.
    EVENT_SLIDE_CREDITSMENU,	// Slide to the credits menu.
    EVENT_SLIDE_OPTIONSMENU,	// Slide to the options menu.
    EVENT_STARTEASY,        	// Start a new game on easy.
    EVENT_STARTNORMAL,        	// Start a new game on normal.
    EVENT_STARTHARD,        	// Start a new game on hard.
    EVENT_MAINMENU,         	// Load the main menu as the next screen.
    EVENT_DISPLAYMESSAGE,   	// Display a message to the user.
    EVENT_INPUT_ACTIVATE,		// Activate input.
    EVENT_INPUT_DEACTIVATE,		// Deactivate input.
    EVENT_QUIT,             	// Quit the game.
    EVENT_NULL              	// Null event.
};

#endif /* EVENT_HPP_ */
