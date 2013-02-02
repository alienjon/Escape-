/*
 * AnimatedSprite.hpp
 *
 *  Created on: Jan 31, 2013
 *      Author: alienjon
 */
#ifndef ANIMATEDSPRITE_HPP_
#define ANIMATEDSPRITE_HPP_

#include <list>
#include <utility>

#include "SFML/Graphics.hpp"

#include "../Engine/Timer.hpp"

/*
 * @brief An animated image.
 *
 * With an animated sprite you have access to adding and removing individual image
 * sprites of the animation and set the offset speed between image changes.
 *
 * @note As of right now this is basically a container class for the sprites, so any
 * graphic-specific changes (ie: rotation, scaling) must be done at the sf::Sprite level.
 *
 * @note Credit goes to SFML for much of the code in this class, as it is based off of sf::Sprite
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
	public:
	/**
	 * @brief Default constructor.
	 * @param speed Optional parameter to set the amount of time (in ms) between displaying the next image.
	 */
	AnimatedSprite(unsigned int speed = 100);
	virtual ~AnimatedSprite();

	/**
	 * @brief Add a frame to the animation.
	 * @param frame The frame to add.
	 */
	void addFrame(const sf::Texture& frame);

	/**
	 * @brief Add a frame to the animation.
	 * @param frame The frame to add.
	 * @param drawArea The area of the sprite to draw.
	 */
	void addFrame(const sf::Texture& frame, const sf::IntRect& drawArea);

	/**
	 * @brief Clear the animation of all images and reset the initial frame.
	 */
	void clear();

	/**
	 * @brief Draw the next animation frame to the target.
	 * @param target The render target to draw onto.
	 * @param states State information for the render target.
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * @brief Get the current animation speed.
	 * @return The animation speed.
	 */
	unsigned int getAnimationSpeed() const;

	/**
	 * @brief Get the alpha value of the sprite.
	 * @return The alpha value.
	 */
	unsigned int getAlpha() const;

	/**
	 * @brief Get the color of the sprite.
	 * @return The color.
	 */
	const sf::Color& getColor() const;

	/**
	 * @brief Calculate the dimension of the sprite without translations (ie: rotation, scale, etc...) taken into account.
	 * @return The local bounds.
	 */
	sf::FloatRect getLocalBounds() const;

	/**
	 * @brief Calculate the dimension of the sprite with translations included (ie: rotation, scale, etc...).
	 * @return The global bounds.
	 */
	sf::FloatRect getGlobalBounds() const;

	/**
	 * @brief Get the height of the animated sprite.
	 * @return The height.
	 */
	unsigned int getHeight() const;

	/**
	 * @brief Returns the texture of the current frame.
	 * @return The current texture.
	 */
	const sf::Texture& getTexture() const;

	/**
	 * @brief Returns the texture display area of the current frame.
	 * @return The area of the current frame being displayed.
	 */
	const sf::IntRect& getTextureRect() const;

	/**
	 * @brief Get the width of the sprite.
	 * @return The width.
	 */
	unsigned int getWidth() const;

	/**
	 * @brief Update the animated sprite.
	 */
	virtual void logic();

	/**
	 * @brief Set the alpha of the sprites.
	 * @param alpha The alpha value.
	 */
	void setAlpha(unsigned int alpha);

	/**
	 * @brief Set the current animation speed.
	 * @param speed The new animation speed (in ms).
	 */
	void setAnimationSpeed(unsigned int speed);

	/**
	 * @brief Set the color for all current frames of the sprite.
	 * @param color The color to set.
	 */
	void setColor(const sf::Color& color);

	private:
	/**
	 * @brief Update the location of the vertices.
	 */
	void mUpdatePositions();

	/**
	 * @brief Update the texture coordinates.
	 */
	void mUpdateTexCoords();

	// The display area of the sprite.
	sf::Vertex mVertices[4];

	// The animation images.
	std::list<std::pair<const sf::Texture&, sf::IntRect> > mAnimation;

	// The current image.
	std::list<std::pair<const sf::Texture&, sf::IntRect> >::iterator mAnimationFrame;

	// The length of time (in ms) between displaying images.
	unsigned int mAnimationSpeed;

	// The animation timer.
	Timer mAnimationTimer;

	// The alpha value of the sprite.
	unsigned int mAlpha;
};

#endif /* ANIMATEDSPRITE_HPP_ */
