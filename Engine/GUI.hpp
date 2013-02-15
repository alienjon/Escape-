/*
 * Gui.hpp
 *
 *  Created on: Nov 4, 2011
 *      Author: alienjon
 */
#ifndef GUI_HPP
#define GUI_HPP

#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

/**
 * @brief The game's base Gui object.
 */
class GUI : public gcn::Gui
{
	public:
    /**
     * @brief Construct a new GUI object.
     * @param graphics The graphics object.
     */
    GUI(gcn::SFMLGraphics& graphics, gcn::SFMLInput& input);

    /**
     * @brief Sets the base widget for the root container.
     * @param container The container to set.
     */
    void setBase(gcn::Container* container);

    /**
     * @brief Set the size of the gui.
     * @param width The gui width.
     * @param height The gui height.
     */
    void setSize(unsigned int width, unsigned int height);

	protected:
	// The root container is the bottom container in which all other widgets feed out from.
	gcn::Container mRoot;
};

#endif
