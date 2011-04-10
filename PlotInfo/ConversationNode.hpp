/*
 * ConversationNode.hpp
 *
 *  Created on: Jun 24, 2010
 *      Author: the-saint
 */
#ifndef CONVERSATIONNODE_HPP_
#define CONVERSATIONNODE_HPP_

#include <string>

#include "PlotNode.hpp"

/**
 * @brief A plot node for conversations.
 */
class ConversationNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The node's keyword.
	 * @param activate The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param caption The caption for the message box.
	 * @param sprite The sprite keyword.
	 * @param text The text of the conversation.
	 *
	 * @note The deactivation keyword is an in-game keyword for conversations.  Therefore it is not needed for conversations.
	 */
	ConversationNode(const std::string& keyword, const NodeKeywordSet& activate, const NodeKeywordSet& deactivation, const std::string& caption, const std::string& sprite, const std::string& text);

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	/**
	 * @brief A plot event occurred.
	 * @param event The plot event.
	 */
	virtual void plotOccurance(const PlotEvent& event);

	private:
	/**
	 * The message box's caption.
	 */
	std::string mCaption;

	/**
	 * The sprite keyword.
	 */
	std::string mSprite;

	/**
	 * The conversation's dialog.
	 */
	std::string mText;
};

#endif /* CONVERSATIONNODE_HPP_ */
