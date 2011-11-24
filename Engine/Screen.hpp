/*
 * Screen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <SFML/Graphics.hpp>

#include "../Interfaces/GCNActionInterface.hpp"
#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"
#include "../Engine/Logger.hpp"

/*
 * @brief A screen is an abstract way of looking at what's going on.
 */
class Screen : public gcn::ActionListener, public GCNActionInterface, public gcn::KeyListener, public gcn::MouseListener
{
    public:
    virtual ~Screen()
    {}

    /**
     * @brief An action occurred.
     * @param event The event details.
     */
    virtual void action(const gcn::ActionEvent& event)
    {}

    /**
     * @brief Add a key listener.
     * @param listener Listener
     */
    inline void addKeyListener(gcn::KeyListener* listener)
    {
    	mKeyListeners.push_back(listener);
    }

    /**
     * @brief Add a mouse listener.
     * @param listener The listener.
     */
    inline void addMouseListener(gcn::MouseListener* listener)
    {
    	mMouseListeners.push_back(listener);
    }

    /**
     * @brief Draw, from gcn::Widget.
     * @param graphics The graphics object with which to draw.
     */
    virtual void draw(gcn::Graphics* graphics)
    {}

    /**
     * @brief Draw the screen.
     * @param renderer The renderer with which to draw.
     */
    virtual void draw(gcn::SFMLGraphics& renderer) = 0;

    /**
     * @brief Get the height of the screen.
     * @return The height of the screen.
     */
    inline unsigned int getHeight() const
    {
    	return mBase.getHeight();
    }

    /**
     * @brief Get the width of the screen.
     * @return The width of the screen.
     */
    inline unsigned int getWidth() const
    {
    	return mBase.getWidth();
    }

    /**
     * @brief Checks to see if the screen is still doing stuff.
     * @return True only if the screen has finished what it is doing.
     */
    inline bool isDone() const
    {
        return mDone;
    }

    /**
     * @brief A key was pressed.
     * @param event The key event.
     */
    virtual void keyPressed(gcn::KeyEvent& event)
    {
    	mDistributeKeyEvent(event, gcn::KeyEvent::PRESSED);
    }

    /**
     * @brief A key was released.
     * @param event The key event.
     */
    virtual void keyReleased(gcn::KeyEvent& event)
    {
    	mDistributeKeyEvent(event, gcn::KeyEvent::RELEASED);
    }

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui is provided for screen GUI management.
     */
    virtual void load(GUI* gui){};

    /**
     * @brief Perform logic.
     */
    virtual void logic() = 0;

    /**
     * @brief Mouse entered event.
     * @param event The event.
     */
    virtual void mouseEntered(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::ENTERED);
    }

    /**
     * @brief Mouse exited event.
     * @param event The event.
     */
    virtual void mouseExited(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::EXITED);
    }

    /**
     * @brief Mouse pressed event.
     * @param event The event.
     */
    virtual void mousePressed(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::PRESSED);
    }

    /**
     * @brief Mouse released event.
     * @param event The event.
     */
    virtual void mouseReleased(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::RELEASED);
    }

    /**
     * @brief Mouse clicked event.
     * @param event The event.
     */
    virtual void mouseClicked(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::CLICKED);
    }

    /**
     * @brief Mouse wheel moved up event.
     * @param event The event.
     */
    virtual void mouseWheelMovedUp(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::WHEEL_MOVED_UP);
    }

    /**
     * @brief Mouse wheel moved down event.
     * @param event The event.
     */
    virtual void mouseWheelMovedDown(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::WHEEL_MOVED_DOWN);
    }

    /**
     * @brief Mouse moved event.
     * @param event The event.
     */
    virtual void mouseMoved(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::MOVED);
    }

    /**
     * @brief Mouse dragged event.
     * @param event The event.
     */
    virtual void mouseDragged(gcn::MouseEvent& event)
    {
    	mDistributeMouseEvent(event, gcn::MouseEvent::DRAGGED);
    }

    /**
     * @brief Remove a key listener.
     * @param listener The listener.
     */
    inline void removeKeyListener(gcn::KeyListener* listener)
    {
    	mKeyListeners.remove(listener);
    }

    /**
     * @brief Remove a mouse listener.
     * @param listener The listener.
     */
    inline void removeMouseListener(gcn::MouseListener* listener)
    {
    	mMouseListeners.remove(listener);
    }

    /**
     * @brief Set the height of the screen.
     * @param height The height of the screen.
     */
    inline void setHeight(unsigned int height)
    {
    	mBase.setHeight(height);
    }

    /**
     * @brief Set the size of the screen.
     * @param width The width of the screen.
     * @param height The height of the screen.
     */
    inline void setSize(unsigned int width, unsigned int height)
    {
    	mBase.setSize(width, height);
    }

    /**
     * @brief Set the width of the screen.
     * @param width The screen width.
     */
    inline void setWidth(unsigned int width)
    {
    	mBase.setWidth(width);
    }

    /**
     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
     */
    virtual void unload(){};

    protected:
    /**
     * @brief Construct a screen.
     * @note You need to call setSize() or setWidth()/setHeight() prior to using the screen.
     */
    Screen() :
    	mDone(false)
    {
        // They should not, however, draw anything superfluous to hide the root GUI widget.
        mBase.setOpaque(false);

        // Make sure the screen can receive focus.
        mBase.setFocusable(true);

        // Set the listeners.
        mBase.addKeyListener(this);
        mBase.addMouseListener(this);
    }

    /**
     * The state of the screen (false if it is still doing stuff)
     * @note This needs to be set to true when the screen has finished what it is doing (CANNOT be called in unload())
     */
    bool mDone;

    // The base widget for this screen.
    gcn::Container mBase;

    private:
    /**
     * @brief Distribute a key event.
     * @param event The event that occurred.
     * @param type The event type.
     */
    void mDistributeKeyEvent(gcn::KeyEvent& event, unsigned int type)
    {
    	for(std::list<gcn::KeyListener*>::iterator it = mKeyListeners.begin(); it != mKeyListeners.end(); it++)
    	{
    		switch(type)
    		{
    			case gcn::KeyEvent::PRESSED:
    			{
    				(*it)->keyPressed(event);
    				break;
    			}
    			case gcn::KeyEvent::RELEASED:
    			{
    				(*it)->keyReleased(event);
    				break;
    			}
    			default:
    				Logger::warn("Invalid key type provided.");
    		}
    	}
    }

    /**
     * @brief Distribute a mouse event.
     * @param event The event that occurred.
     * @param type The event type.
     */
    void mDistributeMouseEvent(gcn::MouseEvent& event, unsigned int type)
    {
    	for(std::list<gcn::MouseListener*>::iterator it = mMouseListeners.begin(); it != mMouseListeners.end(); it++)
    	{
    		switch(type)
    		{
    			case gcn::MouseEvent::ENTERED:
    			{
    				(*it)->mouseEntered(event);
    				break;
    			}
    			case gcn::MouseEvent::EXITED:
				{
					(*it)->mouseExited(event);
					break;
				}
    			case gcn::MouseEvent::PRESSED:
				{
					(*it)->mousePressed(event);
					break;
				}
    			case gcn::MouseEvent::RELEASED:
				{
					(*it)->mouseReleased(event);
					break;
				}
    			case gcn::MouseEvent::CLICKED:
				{
					(*it)->mouseClicked(event);
					break;
				}
    			case gcn::MouseEvent::WHEEL_MOVED_UP:
				{
					(*it)->mouseWheelMovedUp(event);
					break;
				}
    			case gcn::MouseEvent::WHEEL_MOVED_DOWN:
				{
					(*it)->mouseWheelMovedDown(event);
					break;
				}
    			case gcn::MouseEvent::MOVED:
				{
					(*it)->mouseMoved(event);
					break;
				}
    			case gcn::MouseEvent::DRAGGED:
				{
					(*it)->mouseDragged(event);
					break;
				}
    			default:
    				Logger::warn("Invalid mouse type provided.");
    		}
    	}
    }

    // The list of listeners.
    std::list<gcn::KeyListener*> mKeyListeners;
    std::list<gcn::MouseListener*> mMouseListeners;
};

#endif /* SCREEN_HPP_ */
