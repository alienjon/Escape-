/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <stdexcept>

#include "../Managers/AnimationManager.hpp"
#include "../Entities/Creatures/Creature.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Non-Creatures/Flashlight.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../Actions/MoveToAction.hpp"
#include "../Entities/Non-Creatures/Object.hpp"
#include "../Managers/PlotManager.hpp"

using std::runtime_error;
using std::string;

GameScreen::GameScreen() :
	mIsPaused(false),
	mLevel(0)

{
	// Listen for when the game over widget's buttons are pressed.
	mGameOverWidget.addEventListener(this);
	mGameOverWidget.addActionListener(this); // @todo use Guichan's action events instead of my own events.  This will require removing the EventListeners, etc...

	// Configure the widgets.
	mOptionsMenu.setSize(mBase.getWidth() / 2, mBase.getHeight() / 2);
	mMessageOSD.setWidth(mBase.getWidth() / 2);
	mMessageOSD.setPosition((mBase.getWidth() / 2) - (mMessageOSD.getWidth() / 2), mBase.getHeight() / 5);

	// Configure the action listeners.
	mMessageOSD.addActionListener(this);
	mBase.addKeyListener(&mMessageOSD);

	// Other configuration.
	mPlotManager.setInterfaceListener(this);
	mPlotManager.addEventListener(this);

	// Start the input timer.
	mInputTimer.start();
}

GameScreen::~GameScreen()
{
	mGameOverWidget.removeEventListener(this);
	mGameOverWidget.removeActionListener(this);
	mMessageOSD.removeActionListener(this);
	mBase.removeKeyListener(&mMessageOSD);
	mPlotManager.setInterfaceListener(0);
	mPlotManager.removeEventListener(this);
}

void GameScreen::mAddCreature(const std::string& data)
{
	// If only the name was provided then search for and add an already created entity (warn if not found by that name).  Otherwise
	// the rest of the data details the entity.
	if(mLevel)
	{
		// Get the entity's name and separate it from the details.
		string::size_type pos = 0;
		string name = extractDataLine(data, pos, CHAR_DELIMITER);
		int x = toInt(extractDataLine(data, pos, CHAR_DELIMITER)),
			y = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		string details = data.substr(pos);

		// If the details are empty, then search for the name and add it to the level.
		Entity* entity = mGameData.getEntityByName(name);

		// If an entity was not yet created (it doesn't already exist) and no details to create one were provided, then error.
		if(!entity && details.empty())
		{
			Logger::warn("No entity with name '" + name + "' exists and no details were provided to create one.");
			return;
		}
		// If the entity doesn't exist but details were provided, then create a new entity.
		else if(!entity)
		{
			string tmpl = extractDataLine(data, pos, CHAR_DELIMITER),
				   alig = extractDataLine(data, pos, CHAR_DELIMITER);
			int health  = toInt(extractDataLine(data, pos, CHAR_DELIMITER)),
				defense = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
			entity = mGameData.createCreature(name, tmpl, alig, health, defense);
		}

		// An entity now exists.  Double check and then add it to the current level.
		if(!entity)
		{
			throw runtime_error("GameScreen::eventOccurred() -> Creature not created, but details were provided.");
		}
		else
		{
			// Set the position and add the entity.
			entity->setPosition(x, y);
			mLevel->addEntity(entity);
		}
	}
	else
	{
		Logger::warn("Cannot add an entity with details '" + data + "' because no level currently exists.");
	}
}

void GameScreen::mAddFlashlight(const std::string& data)
{
	// If only the name was provided then search for and add an already created entity (warn if not found by that name).  Otherwise
	// the rest of the data details the entity.
	if(mLevel)
	{

		// Get the entity's name and separate it from the details.
		string::size_type pos = 0;
		string name = extractDataLine(data, pos, CHAR_DELIMITER);
		int x = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		int y = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		string details = data.substr(pos);

		// First try to find the entity.
		Entity* entity = mGameData.getEntityByName(name);

		// If an entity was not yet created (it doesn't already exist) and no details to create one were provided, then error.
		if(!entity && !details.empty())
		{
			// In the case of a flashlight, the rest of the data contains the animation tmeplate, the shining distance, and the shining span.
			string tmpl = extractDataLine(data, pos, CHAR_DELIMITER);
			unsigned int distance = toInt(extractDataLine(data, pos, CHAR_DELIMITER)),
						 span 	  = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
			entity = mGameData.createFlashlight(name, tmpl, distance, span);
		}
		// If the entity doesn't and no details were provided, just warn (no need to error).
		else if(!entity)
		{
			Logger::warn("No entity with name '" + name + "' exists and no details were provided to create one.");
			return;
		}

		// An entity now exists.  Double check and then add it to the current level.
		if(!entity)
		{
			throw runtime_error("GameScreen::eventOccurred() -> Object not created, but details were provided.");
		}
		else
		{
			// Set the position and add the entity.
			entity->setPosition(x, y);
			mLevel->addEntity(entity);
		}
	}
	else
	{
		Logger::warn("Cannot add an entity with details '" + data + "' because no level currently exists.");
	}
}

void GameScreen::mAddObject(const std::string& data)
{
	// If only the name was provided then search for and add an already created entity (warn if not found by that name).  Otherwise
	// the rest of the data details the entity.
	if(mLevel)
	{
		// Get the entity's name and separate it from the details.
		string::size_type pos = 0;
		string name = extractDataLine(data, pos, CHAR_DELIMITER);
		int x = toInt(extractDataLine(data, pos, CHAR_DELIMITER)),
			y = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		string details = extractDataLine(data, pos, CHAR_DELIMITER);

		// First try to find the entity.
		Entity* entity = mGameData.getEntityByName(name);

		// If an entity was not yet created (it doesn't already exist) and no details to create one were provided, then error.
		if(!entity && !details.empty())
		{
			// In the case of an object, the rest of the data is only a template.  Just to make sure, only get to the next delimiter.
			string tmpl = extractDataLine(data, pos, CHAR_DELIMITER);
			entity = mGameData.createObject(name, tmpl);
		}
		// If the entity doesn't and no details were provided, just warn (no need to error).
		else if(!entity)
		{
			Logger::warn("No entity with name '" + name + "' exists and no details were provided to create one.");
			return;
		}

		// An entity now exists.  Double check and then add it to the current level.
		if(!entity)
		{
			throw runtime_error("GameScreen::eventOccurred() -> Object not created, but details were provided.");
		}
		else
		{
			// Set the position and add the entity.
			entity->setPosition(x, y);
			mLevel->addEntity(entity);
		}
	}
	else
	{
		Logger::warn("Cannot add an entity with details '" + data + "' because no level currently exists.");
	}
}

void GameScreen::mCreatureConfig(const std::string& data)
{
	// First get the creature.
	string::size_type pos = 0;
	string name = extractDataLine(data, pos, CHAR_DELIMITER);

	// Creature gotten, now determine what is being done and do it.
	string setting = extractDataLine(data, pos, CHAR_DELIMITER);
	Entity* entity = mGameData.getEntityByName(name);
	if(!entity)
	{
		Logger::warn("Creature with name '" + name + "' not yet created.  Create it before configuring it.");
		return;
	}
	else if(entity->getType() != ENTITY_CREATURE && entity->getType() != ENTITY_PLAYER)
	{
		Logger::warn("Entity with name '" + name + "' is not a creature. Configuring " + setting + " skipped.");
		return;
	}
	Creature* creature = dynamic_cast<Creature*>(entity);

	// Configure...
	if(setting == KEYWORD_CREATURE_SET_WANDER)
	{
		// Tell the creature to wander.
		creature->setWandering(true);
		creature->wander();
	}
	else if(setting == KEYWORD_CREATURE_SET_STOP)
	{
		// Tell the creature to stop.
		creature->stop();
	}
	else if(setting == KEYWORD_CREATURE_SET_SEARCHAREA)
	{
		// Set the search area.
		unsigned int span = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		unsigned int distance = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
		creature->setSearchArea(span, distance);
	}
	else if(setting == KEYWORD_CREATURE_SET_FACINGDIRECTION)
	{
		// Get the direction.
		string dir_str = extractDataLine(data, pos, CHAR_DELIMITER);
		Direction dir = getDirection(toInt(dir_str));
		if(dir == DIR_NONE)
		{
			Logger::warn("'" + dir_str + "' is an invalid direction.");
			return;
		}
		creature->lookAt(getPointInDirection(creature->getVisibleArea().getCenter(), dir, 1));
	}
	else if(setting == KEYWORD_CREATURE_SET_FACINGENTITY)
	{
		// Get the entity.
		string entity_name = extractDataLine(data, pos, CHAR_DELIMITER);
		Entity* entity = mGameData.getEntityByName(entity_name);
		if(!entity)
		{
			Logger::warn("Entity with name '" + entity_name + "' not found.  Unable to look at it.");
			return;
		}
		creature->lookAt(entity->getPosition());
	}
	else if(setting == KEYWORD_CREATURE_SET_ALIGNMENT)
	{
		// Set the creature's alignment.
		creature->setAlignment(extractDataLine(data, pos, CHAR_DELIMITER));
	}
	else if(setting == KEYWORD_CREATURE_SET_SEARCHING)
	{
		// Set the searching state.
		creature->setSearching((extractDataLine(data, pos, CHAR_DELIMITER) == "TRUE") ? true : false);
	}
	else if(setting == KEYWORD_CREATURE_KILL)
	{
		// Kill the creature.
		creature->kill();
	}
	else
	{
		Logger::warn(setting + " is an invalid creature configuration setting.");
	}
}

void GameScreen::mCreatureWalkTo(const std::string& data, CreatureMovedToPointListener* listener)
{
	// The position in the content string and the name.
	string::size_type pos = 0;
	string name = extractDataLine(data, pos, CHAR_DELIMITER);

	// Find the creature (it'll first be an entity.
	Entity* entity = mGameData.getEntityByName(name);

	// If the entity was not found, then warn.
	if(!entity)
	{
		Logger::error("Entity with name '" + name + "' not found.");
		return;
	}

	// Make sure the entity is a creature, otherwise error.
	Creature* creature = dynamic_cast<Creature*>(entity);
	if((entity->getType() != ENTITY_CREATURE || entity->getType() != ENTITY_PLAYER) && !creature)
	{
		Logger::error("Entity with name '" + name + "' is not a creature.");
		return;
	}

	// Move the creature.
	int x = toInt(extractDataLine(data, pos, CHAR_DELIMITER)),
		y = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
	creature->addAction(new MoveToAction(*creature, Vector(x, y)));

	// If a creature moved listener was provided then add the creature as the listener.
	if(listener)
	{
		creature->addCreatureMovedToPointListener(listener);
	}
}

void GameScreen::mDisplaySimpleMessage(const string& message, unsigned int duration)
{
	mSimpleMessageOSD.displayMessage(message, duration);
	mSimpleMessageOSD.setPosition((mBase.getWidth() / 2) - (mSimpleMessageOSD.getWidth() / 2),
								  mBase.getHeight() - mSimpleMessageOSD.getHeight() - mSimpleMessageOSD.getFrameSize());
}

void GameScreen::mRemoveEntity(const std::string& data)
{
	// If an entity removal request is made, it is only removed from the level (the object itself is not deleted).
	if(mLevel)
	{
		mLevel->removeEntity(data);
	}
	else
	{
		Logger::warn("Cannot remove entity with name '" + data + "' because there is no level currently loaded.");
	}
}

void GameScreen::action(const gcn::ActionEvent& event)
{
	// If the message OSD sends a signal, then the player has just pressed an action button in the message box.
	if(event.getSource() == &mMessageOSD)
	{
		// The message box is to be closed.
		mMessageOSD.setVisible(false);

		// Tell the plots that the conversation closed.
		mPlotManager.plotOccurance(PlotEvent(event.getId(), ""));
	}
}

void GameScreen::addCreatureDisplay(Creature* creature)
{
	mHealthBarContainer.add(creature);
}

void GameScreen::addMessage(const std::string& title, const std::string& message)
{
	// When a message is received, tell the player.
	mDisplaySimpleMessage("Message Received", 3000);

	// Add the message.
	mOptionsMenu.addMessage(title, message);
}

unsigned int GameScreen::addTask(const std::string& title, const std::string& message)
{
	// When a task is received, display a simple message to the user.
	mDisplaySimpleMessage(title, 3000);

	// Also add the task to the options menu and return its ID for reference later.
	return mOptionsMenu.addTask(title, message);
}

void GameScreen::completeTask(unsigned int id)
{
	// Indicate that the task is complete.
	mOptionsMenu.completeTask(id);

	// Display a message that the task is complete.
	mDisplaySimpleMessage("Task Complete", 3000);
}

void GameScreen::displayMessage(const string& caption, const string& message, const string& sprite, const string& keyword)
{
	Sprite anim;
	try
	{
		anim = AnimationManager::get(sprite);
	}
	catch(runtime_error& e)
	{
		anim = AnimationManager::get(ANIMATION_NULL_CONVERSATION);
	}

	// Show the message.
	mMessageOSD.setVisible(true);
	mMessageOSD.set(caption, message, anim);
	mMessageOSD.setActionEventId(keyword);
	mMessageOSD.requestFocus();
	mMessageOSD.requestMoveToTop();
}

void GameScreen::draw(Renderer& renderer)
{
    // Set the drawing area based on the viewport.
	renderer.pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

    // Draw any screen objects.
    mLevel->draw(renderer);

    // Pop the drawing area.
    renderer.popClipArea();

    // Apply the layers before drawing the cursor.
    renderer.applyLayers();
}

void GameScreen::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToVectorListener)
{
    // If the event is to quit or to load the main menu, then we are done.
    switch(event)
    {
    	case EVENT_CREATURE_ADD:
    	{
    		mAddCreature(content);
    		break;
    	}
    	case EVENT_CREATURE_CONFIG:
    	{
    		mCreatureConfig(content);
    		break;
    	}
    	case EVENT_CREATURE_WALKTO:
    	{
    		mCreatureWalkTo(content, creatureMovedToVectorListener);
    		break;
    	}
    	case EVENT_OBJECT_ADD:
    	{
    		mAddObject(content);
    		break;
    	}
    	case EVENT_FLASHLIGHT_ADD:
    	{
    		mAddFlashlight(content);
    		break;
    	}
    	case EVENT_ENTITY_REMOVE:
    	{
    		mRemoveEntity(content);
    		break;
    	}
    	case EVENT_PLOTOCCURRENCE:
    	{
    		// The content up to the delimiter in this case is the keyword of whatever just occurred.
    		// After the delimiter is the details.
    		string::size_type pos = 0;
    		string keyword = extractDataLine(content, pos, CHAR_DELIMITER),
    			   details = content.substr(pos);
    		mPlotManager.plotOccurance(PlotEvent(keyword, details));
    		break;
    	}
    	case EVENT_GOTO:
    	{
    		// The content is comprised of the following:
    		// {level name}:{x position}:{y position}
    		// If the level name is blank, then the player will be moved to the provided point in the current level.
    		mNextLevel = content;
    		break;
    	}
    	case EVENT_SAVE:
    	{
    		mDisplaySimpleMessage("Game Saved", 3000);
    		break;
    	}
    	case EVENT_LOAD:
    	{
    		mDisplaySimpleMessage("Game Loaded", 3000);
    		break;
    	}
    	case EVENT_PAUSE:
    	{
    		mIsPaused = true;
    		break;
    	}
    	case EVENT_UNPAUSE:
    	{
    		mIsPaused = false;
    		break;
    	}
        case EVENT_INPUT_ACTIVATE:
        {
        	// Get the player and halt input.
        	mGameData.getPlayer()->setInputState(true);
        	break;
        }
        case EVENT_INPUT_DEACTIVATE:
        {
        	mGameData.getPlayer()->setInputState(false);
        	break;
        }
        case EVENT_ENTITYDISPLAY_ADD:
        {
        	// Get the entity.
        	Entity* entity = mGameData.getEntityByName(content);

        	if(!entity)
        	{
        		Logger::log("Entity with name '" + content + "' does not exist.  Unable to add a display for it.");
        	}
        	else
        	{
        		mHealthBarContainer.add(entity);
        	}
        	break;
        }
        case EVENT_ENTITYDISPLAY_REMOVE:
        {
        	// Get the entity.
        	Entity* entity = mGameData.getEntityByName(content);

        	if(!entity)
        	{
        		Logger::log("Entity with name '" + content + "' does not exist.  Unable to remove a display for it.");
        	}
        	else
        	{
        		mHealthBarContainer.remove(entity);
        	}
        	break;
        }
        case EVENT_MAINMENU:
        {
        	// The content should be a delimited list of images to show as credits screens before returning to the main menu.
        	// Iterate through them and load them.
        	string::size_type pos = 0;
        	while(pos != content.size())
        	{
        		// Extract the current image and load it.
        		string filename = extractDataLine(content, pos, CHAR_DELIMITER);
        		pushEvent(EVENT_ADDCREDITSCREEN, filename);
        	}

        	// End by adding the main menu.
        	pushEvent(EVENT_MAINMENU);

        	// Don't break, as both EVENT_MAINMENU and EVENT_QUIT need to set mDone.
        }
        case EVENT_QUIT:
        {
            mDone = true;
            break;
        }
        default:
        {
        }
    }

    // Push the event to any additional listeners.
    pushEvent(event, content);
}

Vector GameScreen::getViewportOffset() const
{
	return mViewport.getOffset();
}

void GameScreen::handleInput(const Input& input)
{
	/*  As in the Game object, each conditional will return to avoid repetition of commands. */

	if(mInputTimer.getTime() >= 100)
	{
		// Restart the timer.
		mInputTimer.start();

		if(input.isKeyPressed(SDLK_ESCAPE))
		{
			// If the options menu is open (is visible) then hide it and unpause the game.
			if(mOptionsMenu.isVisible())
			{
				mOptionsMenu.setVisible(false);
			}
			// If the options menu is hidden, the display message is not being shown,
			// and the game is not paused, then show the options and pause the game.
			else if(!mIsPaused && !mMessageOSD.isVisible())
			{
				mOptionsMenu.setVisible(true);
			}
			return;
		}

		if(input.isKeyPressed(SDLK_s) && input.isControlPressed())
		{
			saveGame();
			return;
		}
	}

	// If we're not paused and the message display isn't visible, continue with input.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
        mLevel->handleInput(input);
    }
}

void GameScreen::load(GUI* gui)
{
    // Set the base.
    gui->setBase(&mBase);

    // Setup the in-game options menu.
    mOptionsMenu.setVisible(false);
    mOptionsMenu.adjustSize(); // This MUST be done upon level loading (several internal sizes depend on the fonts having been loaded)
    mBase.add(&mOptionsMenu, (mBase.getWidth() / 2) - (mOptionsMenu.getWidth() / 2), (mBase.getHeight() / 2) - (mOptionsMenu.getHeight() / 2));

    // Setup the game over widget.
    mGameOverWidget.setVisible(false);
    mGameOverWidget.setSize((mBase.getWidth() * 3) / 4, (mBase.getWidth() * 3) / 4);
    mBase.add(&mGameOverWidget, (mBase.getWidth() / 2) - (mGameOverWidget.getWidth() / 2), (mBase.getHeight() / 2) - (mGameOverWidget.getHeight() / 2));

    // Hide the message osd.
    mMessageOSD.setVisible(false);

    // Add the OSDs to the screen.
    mBase.add(&mHealthBarContainer, mBase.getWidth() - mHealthBarContainer.getWidth() - mHealthBarContainer.getFrameSize() - 4, mHealthBarContainer.getFrameSize() + 4);
    mBase.add(&mLetterOSD, mLetterOSD.getFrameSize() + 4, mLetterOSD.getFrameSize() + 4);
    mBase.add(&mMessageOSD);
    mBase.add(&mSimpleMessageOSD);

    // Load the current level (note that the first level is loaded in the GameData object, so DON'T do it here)
    mLevel = mGameData.load();

    // Configure the level.
    mLevel->setInterfaceListener(this);
    mLevel->addEventListener(this);

    // Load the plot information.
    mPlotManager.load();
}

void GameScreen::logic()
{
	// Before any logic has been done, check if the next level should be loaded.
	if(!mNextLevel.empty())
	{
		// Unload the current level.
		mLevel->removeEventListener(this);
		mLevel->unload();

		// Load the next level.
		string::size_type pos = 0;
		string level = extractDataLine(mNextLevel, pos, CHAR_DELIMITER);
		int x = toInt(extractDataLine(mNextLevel, pos, CHAR_DELIMITER)),
			y = toInt(extractDataLine(mNextLevel, pos, CHAR_DELIMITER));
		mLevel = mGameData.getLevel(level);
		mLevel->addEventListener(this);
		mLevel->setInterfaceListener(this);

		// Clear the next level variable.
		mNextLevel.clear();

		// Load the level.
		mLevel->load(Vector(x, y));
	}

    // Only do game logic if the game is not paused and neither the options menu or
	// the message display widget is being shown.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
		// Perform logic.
    	mPlotManager.logic();
		mLevel->logic();
		mViewport.logic();
    }
}

void GameScreen::removeCreatureDisplay(Creature* creature)
{
	mHealthBarContainer.remove(creature);
}

void GameScreen::saveGame()
{
	mGameData.saveGame();
}

void GameScreen::setViewportBounds(const Rectangle& bounds)
{
	mViewport.setBounds(bounds);
}

void GameScreen::setViewportFocus(const Entity* entity)
{
	mViewport.center(entity);
}

void GameScreen::setViewportFocus(int x, int y)
{
	mViewport.center(x, y);
}

void GameScreen::signalLetterIndicator()
{
	mLetterOSD.letterReceived();
}

void GameScreen::unload()
{
	// The level should stop listening for events.
	mLevel->removeEventListener(this);
	mLevel->setInterfaceListener(0);

    // Unset the level.
    mLevel = 0;

    // @todo Here I'll want to make sure the plot information is saved.
}
