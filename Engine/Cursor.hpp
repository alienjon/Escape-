/*
 * Cursor.hpp
 *
 *  Created on: Sep 25, 2009
 *      Author: alienjon
 */

#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include "../Engine/Renderer.hpp"
#include "../Engine/Sprite.hpp"
#include "../Math/Vector.hpp"

/*
 * @brief The in-game cursor.
 */
class Cursor
{
    public:
    /**
     * @brief Default constructor.
     */
    Cursor();

    /**
     * @brief Draw the cursor.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Get the visibility of the cursor.
     * @return The visibility of the cursor.
     */
    virtual bool isVisible() const;

    /**
     * @brief Load the cursor.
     */
    virtual void load();

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    /**
     * @brief Set the cursor's position.
     * @param x The new x coordinate.
     * @param y The new y coordinate.
     */
    virtual void setPosition(int x, int y);

    /**
     * @brief Set the visibility of the cursor.
     * @param state The state to set.
     */
    virtual void setVisible(bool state);

    private:
    /**
     * The cursor's animation.
     */
    Sprite mSprite;

    /**
     * The location of the cursor.
     */
    Vector mPoint;
};

#endif /* CURSOR_HPP_ */
