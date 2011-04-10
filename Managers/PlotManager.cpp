/*
 * PlotManager.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: the-saint
 */
#include "PlotManager.hpp"

#include <fstream>
#include <stdexcept>

#include "../PlotInfo/AddEntityNode.hpp"
#include "../PlotInfo/ConversationNode.hpp"
#include "../PlotInfo/CreatureConfigNode.hpp"
#include "../PlotInfo/DebugNode.hpp"
#include "../PlotInfo/EndGameNode.hpp"
#include "../PlotInfo/EnvironmentNode.hpp"
#include "../PlotInfo/GoToNode.hpp"
#include "../PlotInfo/HoldInputNode.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../PlotInfo/MessageNode.hpp"
#include "../PlotInfo/MusicNode.hpp"
#include "../PlotInfo/PauseNode.hpp"
#include "../PlotInfo/PauseGameNode.hpp"
#include "../PlotInfo/RemoveEntityNode.hpp"
#include "../PlotInfo/SoundNode.hpp"
#include "../PlotInfo/TaskNode.hpp"
#include "../PlotInfo/WalkToNode.hpp"

using std::ifstream;
using std::invalid_argument;
using std::list;
using std::runtime_error;
using std::string;

const string PLOTMANAGER_PLOTFILE = "Plotfile.dat";

PlotManager::PlotManager()
{
}

PlotManager::~PlotManager()
{
	// Delete remaining nodes.
	for(list<PlotNode*>::iterator it = mPlotNodes.begin(); it != mPlotNodes.end(); ++it)
	{
		(*it)->removePlotListener(this);
		delete *it;
	}
}

void PlotManager::addNode(const string& data)
{
	// Get the type and keyword.
	string::size_type pos = 0;
	string type		  = extractDataLine(data, pos, CHAR_DELIMITER);
	string keyword    = extractDataLine(data, pos, CHAR_DELIMITER);

	// Break the activation and deactivation keywords up into sets.
	list<string> activate   = extractDataAsCollection(extractDataLine(data, pos, CHAR_DELIMITER), "+");
	list<string> deactivate = extractDataAsCollection(extractDataLine(data, pos, CHAR_DELIMITER), "+");

	// If any keyword is null, then make it a blank string.
	if(keyword == "NULL")
	{
		keyword = "";
	}

	// Get the event type.
	string event_data = data.substr(pos);

	// Create the device based on the type.
	PlotNode* node = 0;
	string::size_type event_pos = 0;
	if(type == PLOTDEVICE_EVENT_DEBUG)
	{
		node = new DebugNode(keyword, activate, deactivate, event_data);
	}
	else if(type == PLOTDEVICE_EVENT_ENVIRONMENT)
	{
		node = new EnvironmentNode(keyword, activate, deactivate, event_data);
	}
	else if(type == PLOTDEVICE_EVENT_CONVERSATION)
	{
		string caption = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		string sprite  = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		node = new ConversationNode(keyword, activate, deactivate, caption, sprite, event_data.substr(event_pos));
	}
	else if(type == PLOTDEVICE_EVENT_PAUSE)
	{
		node = new PauseNode(keyword, activate, deactivate, toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER)));
	}
	else if(type == PLOTDEVICE_EVENT_GAMEPAUSE)
	{
		string duration = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		node = new PauseGameNode(keyword, activate, deactivate, (duration.empty() || duration == "NULL") ? 0 : toInt(duration));
	}
	else if(type == PLOTDEVICE_EVENT_TASK)
	{
		string title   = extractDataLine(event_data, event_pos, CHAR_DELIMITER),
			   message = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		node = new TaskNode(keyword, activate, deactivate, title, message);
	}
	else if(type == PLOTDEVICE_EVENT_MESSAGE)
	{
		string title = extractDataLine(event_data, event_pos, CHAR_DELIMITER),
			   message=extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		node = new MessageNode(keyword, activate, deactivate, title, message);
	}
	else if(type == PLOTDEVICE_EVENT_GOTO)
	{
		string level  = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		int x = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER)),
			y = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		node = new GoToNode(keyword, activate, level, Vector(x, y));
	}
	else if(type == PLOTDEVICE_EVENT_ADDENTITY)
	{
		node = new AddEntityNode(keyword, activate, deactivate, event_data.substr(event_pos));
	}
	else if(type == PLOTDEVICE_EVENT_REMOVEENTITY)
	{
		node = new RemoveEntityNode(keyword, activate, deactivate, event_data.substr(event_pos));
	}
	else if(type == PLOTDEVICE_EVENT_WALKTO)
	{
		string name = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		Vector p;
		p.x = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		p.y = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		node = new WalkToNode(keyword, activate, deactivate, name, p);
	}
	else if(type == PLOTDEVICE_EVENT_HOLDINPUT)
	{
		node = new HoldInputNode(keyword, activate, deactivate);
	}
	else if(type == PLOTDEVICE_EVENT_MUSIC)
	{
		string music_file = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		unsigned int loops = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		unsigned int fade_in = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		unsigned int fade_out = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		node = new MusicNode(keyword, activate, deactivate, music_file, loops, fade_in, fade_out);
	}
	else if(type == PLOTDEVICE_EVENT_SOUND)
	{
		string sound_file = extractDataLine(event_data, event_pos, CHAR_DELIMITER);
		unsigned int loops = toInt(extractDataLine(event_data, event_pos, CHAR_DELIMITER));
		node = new SoundNode(keyword, activate, deactivate, sound_file, loops);
	}
	else if(type == PLOTDEVICE_EVENT_CREATURECONFIG)
	{
		node = new CreatureConfigNode(keyword, activate, deactivate, event_data.substr(event_pos));
	}
	else if(type == PLOTDEVICE_EVENT_ENDGAME)
	{
		node = new EndGameNode(keyword, activate, deactivate, event_data.substr(event_pos));
	}
	else
	{
		Logger::log("Unrecognized plot device: '" + type + "'.");
	}

	// If the node was created, start listening to it.
	if(node)
	{
		// Finish configuring and adding this node.
		node->addEventListener(this);
		node->addPlotListener(this);
		mPlotNodes.push_back(node);

		// If the node is initially activated then physically activate it.
		if(node->isActivated())
		{
			node->activate();
		}
	}
}

void PlotManager::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
	pushEvent(event, content, creatureMovedToPointListener);
}

void PlotManager::load()
{
	ifstream file(PLOTMANAGER_PLOTFILE.c_str(), ifstream::in);
	if(!file.good())
	{
		throw runtime_error("Unable to open the plotfile.");
	}

	// Iterate through the file extracting the plot devices.
	string current_line;
	while(getline(file, current_line))
	{
		// Ignore blank/commented lines.
		if(current_line.empty() || current_line.at(0) == '#')
		{
			continue;
		}

		// Add the new plot device.
		addNode(current_line);
	}

	// Close the file.
	file.close();
}

void PlotManager::logic()
{
    // Iterate through all the plot nodes.
    list<PlotNode*> nodes_for_removal;
    for(list<PlotNode*>::iterator it = mPlotNodes.begin(); it != mPlotNodes.end(); ++it)
    {
    	// Run the node.
    	if((*it)->run())
    	{
			// Node is performed.
			nodes_for_removal.push_back(*it);
    	}
    }

    // Clean any removal nodes.
    for(list<PlotNode*>::iterator it = nodes_for_removal.begin(); it != nodes_for_removal.end(); ++it)
    {
    	// Stop listening to ... um ... stuff.
    	(*it)->removeEventListener(this);
    	(*it)->removePlotListener(this);

    	// Remove and delete the node.
    	mPlotNodes.remove(*it);
    	delete *it;
    }
    nodes_for_removal.clear();
}

void PlotManager::plotOccurance(const PlotEvent& event)
{
	// Pass the occurance along to the nodes.
	for(list<PlotNode*>::iterator it = mPlotNodes.begin(); it != mPlotNodes.end(); ++it)
	{
		(*it)->plotOccurance(event);
	}
}
