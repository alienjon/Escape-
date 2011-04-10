/*
 * ConversationNode.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: the-saint
 */
#include "ConversationNode.hpp"

#include <stdexcept>

#include "../Managers/AnimationManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Managers/PlotManager.hpp"

using std::runtime_error;
using std::string;

ConversationNode::ConversationNode(const string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivation,
								   const string& caption, const string& sprite,   const string& text) : PlotNode(keyword,
																												 activate,
																												 deactivation),
	mCaption(caption),
	mSprite(sprite),
	mText(text)
{
}

void ConversationNode::activate()
{
	// Display the conversation message initially.
	PlotManager::mDisplayMessage(mCaption, mText, mSprite, mKeyword);//@todo remove? KEYWORD_CONVERSATION_ENDED + CHAR_DELIMITER_ALTERNATE + mKeyword);

	// Deactivate the node so that activate will be called again until the deactivation keyword is passed.
	mIsActivated = false;
}

void ConversationNode::plotOccurance(const PlotEvent& event)
{
	// If a conversation was closed while this conversation is active, then distribute the event.
	if(isActivated() && event.getKeyword() == mKeyword)//@todo remove? KEYWORD_CONVERSATION_ENDED + mKeyword)
	{
		mDistributePlotEvent();
	}

	// Continue with the plot occurrance.
	PlotNode::plotOccurance(event);
}
