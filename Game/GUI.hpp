#ifndef GUI_HPP
#define GUI_HPP

#include "SDL/SDL.h" // @note Needed for guichan/sdl.hpp

#include "guichan.hpp"
#include "guichan/sdl.hpp"

#include "../Widgets/FPSDisplayWidget.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Surface.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief The game's gcn::Gui object.
 *
 * Not only provides an interface to gcn::Gui but also a
 * means to display objects to the screen.
 */
class GUI : public gcn::Gui
{
	public:
    /**
     * @brief Construct a new GUI object.
     * @param renderer The renderer.
     */
    GUI(Renderer* renderer);

    /**
     * @brief Initialize all GUI-related information.
     */
    virtual void initialize();

	/**
	 * @brief Push input to the GUI system.
	 * @param event The event to push.
	 */
	virtual void pushInput(SDL_Event& event);

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

	/**
	 * The input object.
	 */
	gcn::SDLInput mInput;

	/**
	 * The FPS display widget.
	 */
	FPSDisplayWidget mFPSDisplayWidget;
};

#endif
