/*
 * SFMLInput.hpp
 *
 *  Created on: Mar 23, 2010
 *      Author: alienjon
 */
#ifndef SFMLINPUT_HPP_
#define SFMLINPUT_HPP_

#include <queue>
#include <SFML/Window.hpp>

#include "../input.hpp"
#include "../keyinput.hpp"
#include "../mouseinput.hpp"

namespace gcn
{
	/*
	 * @brief An input stores a snapshot of input for a single frame.
	 */
	class SFMLInput : public Input
	{
		public:
		/**
		 * @brief Convert an sf::Mouse::Button to a gcn::MouseButton
		 * @param button The sf::Mouse::Button to convert.
		 * @return The gcn::Button
		 */
		static int convertSFToGCNButton(sf::Mouse::Button button);

		/**
		 * @brief Convert an sf::Key::Code to a gcn::Key
		 * @param key The sf::Key to convert.
		 * @return The requested gcn::Key.
		 */
		static int convertSFToGCNKey(sf::Keyboard::Key key);

		/**
		 * @brief Checks whether the numberpad is being used.
		 * @param event The sf::Event.
		 * @return True if the numpad is being used.
		 */
		static bool isNumpad(const sf::Event& event);

		/**
		 * @brief Default constructor.
		 */
		SFMLInput();

		/**
		 * @brief Poll for the current input state.
		 */
		virtual void _pollInput()
		{}

		/**
		 * @brief Process the key states.
		 * @return The key input states.
		 */
		virtual KeyInput dequeueKeyInput();

		/**
		 * @brief Process the mouse states.
		 * @return The mouse input states.
		 */
		virtual MouseInput dequeueMouseInput();

		/**
		 * @brief True if the key queue is empty.
		 * @return True if the key queue is empty.
		 */
		virtual bool isKeyQueueEmpty()
		{
			return mKeyQueue.empty();
		}

		/**
		 * @brief True if the mouse queue is empty.
		 * @return True if the mouse queue is empty.
		 */
		virtual bool isMouseQueueEmpty()
		{
			return mMouseQueue.empty();
		}

		/**
		 * @brief Push an sf::Event onto the input stack.
		 * @param event The event to push.
		 */
		virtual void pushInput(sf::Event& event);

		private:
		// The key and mouse queues.
		std::queue<KeyInput> mKeyQueue;
		std::queue<MouseInput> mMouseQueue;

		// True if a mouse button is pressed (for window focus purposes)
		bool mMouseDown;

		// The time stamp clock;
		sf::Clock mTimestampClock;
	};
}

#endif /* INPUT_HPP_ */
