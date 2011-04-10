/*
 * PlotNode.cpp
 *
 *  Created on: Jun 23, 2010
 *      Author: the-saint
 */
#include "PlotNode.hpp"

using std::list;
using std::string;

PlotNode::PlotNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation) :
	mKeyword(keyword),
	mIsActivated(activation.empty()),
	mIsPerformed(false)
{
	// If the activation set is not empty, then the first item is the primary activation keyword.
	if(!activation.empty())
	{
		// Set the primary.
		NodeKeywordSet::const_iterator it = activation.begin();
		mActivationKeyword = *it;
		mActivationKeyword = (mActivationKeyword == "NULL") ? "" : mActivationKeyword;
		it++;

		mIsActivated = mActivationKeyword.empty();

		// Add the rest as conditional activation keywords.
		for(; it != activation.end(); ++it)
		{
			string to_add(it->substr(1, it->size() - 1));
			if(!to_add.empty() && to_add != "NULL")
			{
				mActivationConditionals.push_back(to_add);
			}
		}
	}

	// If the deactivation set is not empty, then the first item is the primary deactivation keyword.
	if(!deactivation.empty())
	{
		// Set the primary.
		NodeKeywordSet::const_iterator it = deactivation.begin();
		mDeactivationKeyword = *it;
		mDeactivationKeyword = (mDeactivationKeyword == "NULL") ? ""  :mDeactivationKeyword;
		it++;

		// Add the rest as conditional deactivation keywords.
		for(; it != deactivation.end(); ++it)
		{
			string to_add(it->substr(1, it->size() - 1));
			if(!to_add.empty() && to_add != "NULL")
			{
				mDeactivationConditionals.push_back(to_add);
			}
		}
	}
}

PlotNode::~PlotNode()
{
}

void PlotNode::mDistributePlotEvent()
{
	// If the keyword is null, then just ignore this node.
	if(mKeyword.empty())
	{
		return;
	}

	// Create and distribute the event.
	PlotEvent event(mKeyword, ""); // @todo Do I need the data string?

	for(list<PlotListener*>::iterator it = mPlotListeners.begin(); it != mPlotListeners.end(); ++it)
	{
		(*it)->plotOccurance(event);
	}
}

void PlotNode::activate()
{
	// Empty, by default.
}

void PlotNode::addPlotListener(PlotListener* listener)
{
	mPlotListeners.push_back(listener);
}

void PlotNode::creatureMoved(Creature& creature)
{
	// Empty, by default.
}

void PlotNode::deactivate()
{
	// Empty, by default.
}

bool PlotNode::isActivated() const
{
	return mIsActivated;
}

bool PlotNode::logic()
{
	return mIsPerformed;
}

void PlotNode::plotOccurance(const PlotEvent& event)
{
	// If the node is already performed, then don't listen for additional plot occurrances.
	if(mIsPerformed)
	{
		return;
	}

	// Remove the keyword from the conditionals.
	mActivationConditionals.remove(event.getKeyword());
	mDeactivationConditionals.remove(event.getKeyword());

	// A plot node is activated once (unless the specific node unsets the activation state).
	if(!isActivated() && mActivationConditionals.empty() && event.getKeyword() == mActivationKeyword)
	{
		// The node is now activated (do this before calling activate(), in case the specific node unsets the activation state).
		mIsActivated = true;

		// Activate the node.
		activate();
	}

	// A node can only be deactivated if it is already activated.  Null deactivation keywords mean that the node continues forever (so
	// it can't be deactivated).  If those conditions are met then check to see if the deactivation keyword was provided.  If so, then
	// deactivate this node.
	if(!mDeactivationKeyword.empty() && mDeactivationConditionals.empty() && event.getKeyword() == mDeactivationKeyword)
	{
		// The node is now performed (do this before calling deactivate() in case the specific node unsets the performed state).
		mIsPerformed = true;

		// Deactivate the node.
		deactivate();

		// Distribute the plot event.
		mDistributePlotEvent();
	}
}

void PlotNode::removePlotListener(PlotListener* listener)
{
	mPlotListeners.remove(listener);
}

bool PlotNode::run()
{
	// If the plot node is activated but not performed, then perform logic.  If it is then performed then deactivate and distribute the plot events.
	if(!mIsPerformed && isActivated() && (mIsPerformed = logic()))
	{
		deactivate();
		mDistributePlotEvent();
	}

	return mIsPerformed;
}

const string PLOTDEVICE_EVENT_DEBUG = "DBG";
const string PLOTDEVICE_EVENT_ENVIRONMENT = "ENV";
const string PLOTDEVICE_EVENT_CONVERSATION = "CON";
const string PLOTDEVICE_EVENT_PAUSE = "PAU";
const string PLOTDEVICE_EVENT_GAMEPAUSE = "PAG";
const string PLOTDEVICE_EVENT_TASK = "TSK";
const string PLOTDEVICE_EVENT_MESSAGE = "NTE";
const string PLOTDEVICE_EVENT_GOTO = "MOV";
const string PLOTDEVICE_EVENT_ADDENTITY = "ADD";
const string PLOTDEVICE_EVENT_REMOVEENTITY = "REM";
const string PLOTDEVICE_EVENT_WALKTO = "WLK";
const string PLOTDEVICE_EVENT_HOLDINPUT = "HIN";
const string PLOTDEVICE_EVENT_MUSIC = "MUS";
const string PLOTDEVICE_EVENT_SOUND = "SND";
const string PLOTDEVICE_EVENT_CREATURECONFIG = "SET";
const string PLOTDEVICE_EVENT_ENDGAME = "END";
