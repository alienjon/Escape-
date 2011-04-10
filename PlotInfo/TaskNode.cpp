/*
 * TaskNode.cpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */
#include "TaskNode.hpp"

#include "../Managers/PlotManager.hpp"

using std::string;

TaskNode::TaskNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& title, const string& message) : PlotNode(keyword, activation, deactivation),
	mTitle(title),
	mMessage(message),
	mId(0)
{
}

void TaskNode::activate()
{
	// Add the task.
	mId = PlotManager::mAddTask(mTitle, mMessage);
}

void TaskNode::deactivate()
{
	// Complete the task.
	PlotManager::mCompleteTask(mId);
}
