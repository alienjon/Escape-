/*
 * Gui.hpp
 *
 *  Created on: Nov 4, 2011
 *      Author: alienjon
 */
#ifndef GUI_HPP
#define GUI_HPP

#include "../Widgets/FPSDisplayWidget.hpp"
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
     * @brief Remove the widget from the root container.
     * @param widget The widget to remove.
     */
    virtual void remove(gcn::Widget* widget);

    /**
     * @brief Sets the base widget for the root container.
     * @param container The container to set.
     */
    virtual void setBase(gcn::Container* container);

	/**
	 * @brief Toggle the fps state.
	 */
	virtual void toggleFPS();

	protected:
	/**
	 * The root container is the bottom container in which all other widgets feed out from.
	 * The base container is the first container that contains easily-accessible widgets (OSD, for example)
	 */
	gcn::Container mRoot;
	gcn::Container* mBase;

	// The FPS display widget.
	FPSDisplayWidget mFPSDisplayWidget;
};

#endif
