/*
 * Input.hpp
 *
 *  Created on: Mar 23, 2010
 *      Author: alienjon
 */

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <set>

#include "SDL/SDL.h"

#include "../Math/Vector.hpp"

class GUI;

/*
 * @brief An input stores a snapshot of input for a single frame.
 */
class Input
{
	public:
	/**
	 * @brief Default constructor.
	 *
	 * @note The default position for all input is SDL_RELEASED.
	 */
	Input();
	virtual ~Input();

	/**
	 * @brief Unset all data to it's default position (everything is set to RELEASED, essentially).
	 */
	virtual void clear();

	/**
	 * @brief Function to display the input's state.
	 * @note To be used for debugging.
	 */
	void displayInputState() const;

	/**
	 * @brief Get the mouse's current position on the screen.
	 * @return The mouse's current position.
	 */
	virtual const Vector& getMousePosition() const;

	/**
	 * @brief Get the mouse X position on the screen.
	 * @return The x position.
	 */
	virtual const int getMouseX() const;

	/**
	 * @brief Get the mouse Y position on the screen.
	 * @return The y position.
	 */
	virtual const int getMouseY() const;

	/**
	 * @brief Updates the input information and injects input to the provided gui.
	 * @param gui The gui to inject input.
	 */
	virtual void handleInput(GUI* gui);

	/**
	 * @brief Checks if an alt key is pressed.
	 * @return True if an alt key is pressed.
	 */
	virtual bool isAltPressed() const;

	/**
	 * @brief Checks if capslock is enabled.
	 * @return True if capslock is enabled.
	 */
	virtual bool isCapslockPressed() const;

	/**
	 * @brief Checks if a control key is pressed.
	 * @return True if a control key is pressed.
	 */
	virtual bool isControlPressed() const;

	/**
	 * @brief Compares a key to it's previous state.
	 * @param key The key to check.
	 * @return True if the key is currently disabled but was previously enabled.
	 */
	virtual bool isKeyClicked(SDLKey key) const;

	/**
	 * @brief Determines if a particular key is pressed.
	 * @param key The key to check.
	 * @return True if the key is currently pressed.
	 */
	virtual bool isKeyPressed(SDLKey key) const;

	/**
	 * @brief Checks if a meta button is pressed.
	 * @return True if a meta button is pressed.
	 */
	virtual bool isMetaPressed() const;

	/**
	 * @brief Determines if a particular mouse button is pressed.
	 * @param button The button to check.
	 * @return True if the button is pressed.
	 */
	virtual bool isMousePressed(Uint8 button) const;

	/**
	 * @brief Checks if a shift key is pressed.
	 * @return True if a shift key is pressed.
	 */
	virtual bool isShiftPressed() const;

	/**
	 * @brief Set a key's state.
	 * @param key The key to set.
	 * @param state The state to set.
	 */
	virtual void setKeyPressed(SDLKey key, bool pressed = true);

	/**
	 * @brief Set the mouse's position on the screen.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 */
	virtual void setMousePosition(int x, int y);

	/**
	 * @brief Set a mouse button to it's pressed state.
	 * @param button The button.
	 * @param pressed True if the button is pressed, false if not.
	 */
	virtual void setMousePressed(Uint8 button, bool pressed = true);

	private:
    /**
     * The SDL input event (so I don't have to keep creating an object)
     */
    SDL_Event mEvent;

	/**
	 * The keys.
	 */
	std::set<SDLKey> mKeys;
	std::set<SDLKey> mPreviousKeys;

	/**
	 * The mouse buttons.
	 */
	std::set<Uint8> mMouseButtons;

	/**
	 * The mouse location.
	 */
	Vector mMousePosition;

	/**
	 * Modifier keys.
	 */
	bool mAlt, mCaps, mControl, mMeta, mShift;
};

#endif /* INPUT_HPP_ */
