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
	EVENT_CREATURE_ADD,			// An event to add a creature to the game.
	EVENT_CREATURE_CONFIG,		// An event to configure a creature.
	EVENT_CREATURE_WALKTO,		// Tell a creature to walk to a given point.
	EVENT_OBJECT_ADD,			// An event to add an object to the game.
	EVENT_FLASHLIGHT_ADD,		// An event to add a flashlight to the game.
	EVENT_ENTITY_REMOVE,		// An event to remove an entity from the current level.
	EVENT_GOTO,					// An event to move an entity from one spot to another.
	EVENT_PLOTOCCURRENCE,		// A plot event occurred.
	EVENT_PAUSE,				// Pause the game.
	EVENT_UNPAUSE,				// Unpause the game.
    EVENT_SLIDE_MAINMENU,   	// Slide to the main menu.
    EVENT_SLIDE_NEWMENU,    	// Slide to the new menu.
    EVENT_SLIDE_LOADMENU,   	// Slide to the load menu.
    EVENT_SLIDE_CREDITSMENU,	// Slide to the credits menu.
    EVENT_SLIDE_OPTIONSMENU,	// Slide to the options menu.
    EVENT_START,        		// Start a new game.
    EVENT_SAVE,             	// Save the game.
    EVENT_LOAD,             	// Load a game.
    EVENT_MAINMENU,         	// Load the main menu as the next screen.
    EVENT_DISPLAYMESSAGE,   	// Display a message to the user.
    EVENT_NEXTLEVEL,        	// Go to the next level.
    EVENT_PREVIOUSLEVEL,    	// Go to the previous level.
    EVENT_INPUT_ACTIVATE,		// Activate input.
    EVENT_INPUT_DEACTIVATE,		// Deactivate input.
    EVENT_ENTITYDISPLAY_ADD,	// Add a creature display.
    EVENT_ENTITYDISPLAY_REMOVE, // Remove a creature display.
    EVENT_QUIT,             	// Quit the game.
    EVENT_NULL              	// Null event.
};

#endif /* EVENT_HPP_ */
