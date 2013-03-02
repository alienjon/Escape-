/*
 * GUI.hpp
 *
 *  Created on: Feb 19, 2013
 *      Author: alienjon
 */
#ifndef GUI_HPP_
#define GUI_HPP_

#include <map>

#include <CEGUI/CEGUI.h>
#include <SFML/Graphics.hpp>

/**
 * @brief The GUI object handles GUI configuration and initialization.
 *
 * @note Credit goes to the author of the CEGUI SFML tutorial found here:
 * http://www.sfml-dev.org/wiki/en/tutorials/cegui
 *
 * I updated the code for CEGUI 0.79 and SFML 2.0, but some of the code and
 * all of the conceptual design is based off of the author of that tutorial
 * (sorry, I couldn't find the name of the author in any of the code :-/)
 */
class GUI
{
	public:
	/**
	 * @brief Default constructor handles most default setups,
	 *
	 * Make sure that @see initialize() is called after the GUI is constructed
	 * and is ready to be setup.
	 */
	GUI();
	~GUI();

	/**
	 * @brief Handle input.
	 * @param event The input event.
	 * @return True if the event was consumed (used).
	 */
	bool handleInput(sf::Event& event);

	/**
	 * @brief Initialize the GUI.
	 * @note MUST be called after the creation of the rendering window.
	 */
	void initialize();

	/**
	 * @brief Draw the GUI.
	 */
	void draw();

	private:
	/**
	 * @brief Initialize the key maps.
	 */
	void initializeMaps();

	/**
	 * @brief Initialize the resource groups.
	 */
	void initializeResourceGroups();

	// Definitions for the map types.
	typedef std::map<sf::Keyboard::Key, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	// The SFML to CEGUI map containers.
	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;

	// Convert an SFML key to a CEGUI key.
	CEGUI::Key::Scan toCEGUIKey(sf::Keyboard::Key key);

	// Convert an SFML mouse button to a CEGUI mouse button.
	CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button button);
};

#endif /* GUI_HPP_ */
