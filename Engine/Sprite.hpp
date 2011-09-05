/*
 * Sprite.hpp
 *
 *  Created on: Apr 3, 2009
 *      Author: alienjon
 */
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <list>
#include <vector>

#include "../guichan.hpp"

#include "../Listeners/AnimationCycleListener.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "Surface.hpp"
#include "Timer.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief A sprite is essentially an animation.
 *
 * A sprite can contain any number of Surfaces (called frames) and
 * also possesses a logic() method that will iterate through the
 * frames (based on each Surface's pause time) and a draw() method
 * that displays the animation to the screen (via the provided
 * graphics object)
 */
class Sprite
{
	// The animation manager needs to add frames to the sprite.
	friend class AnimationManager;

	public:
	/**
	 * @brief Construct an sprite.
	 */
	Sprite();

	/**
	 * @brief Construct a sprite with a single image.
	 * @param surface The surface.
	 */
	Sprite(Surface* surface);

    /**
     * @brief Add an animation cycle listener.
     * @param listener The listener to add.
     */
    void addAnimationCycleListener(AnimationCycleListener* listener);

	/**
	 * @brief Draw the sprite to the screen.
	 * @param graphics The graphics object to draw with.
	 * @param pos The position at which to draw.
	 */
	virtual void draw(gcn::Graphics* graphics, const Vector& pos);

	/**
	 * @brief Draw the sprite to the screen.
	 * @param graphics The graphics object to draw with.
	 * @param x The x location to draw the sprite.
	 * @param y The y location to draw the sprite.
	 */
	virtual void draw(gcn::Graphics* graphics, const int& x, const int& y);

	/**
	 * @brief Draw the sprite to the screen.
	 * @param renderer The graphics object to draw with.
	 * @param pos The position to draw the sprite.
	 */
	virtual void draw(Renderer& renderer, const Vector& pos);

	/**
	 * @brief Draw the sprite to the screen.
	 * @param renderer The graphics object to draw with.
	 * @param x The x location to draw the sprite.
	 * @param y The y location to draw the sprite.
	 */
	virtual void draw(Renderer& graphics, const int& x, const int& y);

    /**
     * @brief Get the dimension of this sprite.
     * @return A copy of a rectangle that is the current dimension of this sprite.
     */
    const Rectangle& getDimension() const;

    /**
     * @brief Return the current frame.
     * @return The current frame.
     */
    unsigned int getFrame() const;

    /**
     * @brief Get the height of this sprite.
     * @return The height.
     */
    int getHeight() const;

    /**
     * @brief Get the total number of frames.
     * @return The number of frames in this sprite.
     */
    unsigned int getNumberOfFrames() const;

    /**
     * @brief Get the width of this sprite.
     * @return The width.
     */
    int getWidth() const;

	/**
	 * @brief Checks to see if the sprite is currently animating.
	 * @return True if the sprite is animating.
	 */
	bool isAnimating() const;

	/**
	 * @brief Determines the visibility state.
	 * @return False if the sprite is not being draw.
	 */
	bool isVisible() const;

    /**
     * @brief Perform internal logic.
     */
    virtual void logic();

    /**
     * @brief Remove an animation cycle listener.
     * @param listener The listener to remove.
     */
    void removeAnimationCycleListener(AnimationCycleListener* listener);

	/**
	 * @brief Sets the animating state of the sprite.
	 * @param state The state of animation to set.
	 */
	void setAnimating(bool state);

	/**
	 * @brief Set the current frame.
	 * @param frame The frame to set.  The first frame is 0 and the last frame is getNumberOfFrames() - 1.
	 * @note This function throws an out_of_range error if the frame is greater than the number of frames.
	 */
	void setFrame(unsigned int frame);

	/**
	 * @brief Set the visibility state of the sprite.
	 * @param state True if the sprite is to draw itself, false to not draw itself.
	 */
	void setVisible(bool state);

	protected:
	/**
	 * @brief Add a frame to the animation.
	 * @param frame The frame to add.
	 */
	virtual void mAddFrame(Surface* frame);

	/**
	 * @brief Clear the frames.
	 */
	void mClearFrames();

	private:
	/**
	 * This sprite's frames.
	 */
	std::vector<Surface*> mFrames;

	/**
	 * The current frame.
	 */
	std::vector<Surface*>::size_type mCurrentFrame;

	/**
	 * The animation timer.
	 */
	Timer mAnimationTimer;

	/**
	 * The visibility state.
	 */
	bool mIsVisible;

    /**
     * The listeners.
     */
    std::list<AnimationCycleListener*> mAnimationCycleListeners;
};

#endif /* SPRITE_HPP_ */
