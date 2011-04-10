/*
 * DisplayMessageAction.hpp
 *
 *  Created on: May 24, 2010
 *      Author: the-saint
 */

#ifndef DISPLAYMESSAGEACTION_HPP_
#define DISPLAYMESSAGEACTION_HPP_

#include <string>

#include "../Actions/Action.hpp"
#include "../Game/EnvironmentData.hpp"
#include "../Screens/GameScreen.hpp"
#include "../guichan.hpp"

/**
 * @brief An action to tell a GameScreenInterface.
 */
class DisplayMessageAction : public Action
{
	public:
	/**
	 * @brief Default constructor.
	 * @param caption The caption.
	 * @param message The message to display.
	 * @param sprite The keyword of the sprite to display with the message.
	 * @param interface The interface to show the messages.
	 */
	DisplayMessageAction(const std::string& caption, const std::string& message, const std::string& sprite, GameScreen* screen);
	virtual	~DisplayMessageAction();

	/**
	 * @brief Activate the action.
	 */
	virtual void activate(EnvironmentData& eData);

	private:
	/**
	 * The caption.
	 */
	const std::string mCaption;

	/**
	 * The message.
	 */
	const std::string mMessage;

	/**
	 * The sprite keyword.
	 */
	const std::string mImage;

	/**
	 * The interface.
	 */
	GameScreen* mScreen;
};

#endif /* DISPLAYMESSAGEACTION_HPP_ */
