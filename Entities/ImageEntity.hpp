/*
 * ImageEntity.hpp
 *
 *  Created on: Nov 27, 2011
 *      Author: alienjon
 */
#ifndef IMAGEENTITY_HPP_
#define IMAGEENTITY_HPP_

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"

class ImageEntity : public Entity
{
	public:
	/**
	 * @brief Adjust the size of the image entity to the size of the displaying image.
	 */
	virtual void adjustSize();

    /**
     * @brief Draw the entity.
     * @param renderer The renderer with which to draw.
     */
    virtual void draw(sf::RenderWindow& renderer)
    {
    	renderer.Draw(mSprite);
    }

    /**
     * @brief Get the alpha value for the entity.
     * @return The alpha value for the entity.
     */
    virtual unsigned int getAlpha() const
    {
    	return mSprite.GetColor().a;
    }

    /**
     * @brief Get the physical area of this being.
     * @return The dimension.
     */
    virtual const sf::Shape& getDimension()
    {
    	mShape.SetPosition(getPosition());
    	return mShape;
    }

    /**
     * @brief Get the drawable aspect of the entity.
     * @return The drawable aspect of the entity.
     */
    virtual sf::Drawable& getDrawable()
    {
    	return mSprite;
    }

    /**
     * @brief Get the entity's height.
     * @return The entity's height.
     */
    virtual unsigned int getHeight() const
    {
    	return mSprite.GetSize().y;
    }

    /**
     * @brief Get the current position of this entity.
     * @return The current position of this entity.
     */
    virtual const sf::Vector2f& getPosition() const
    {
    	return mSprite.GetPosition();
    }

    /**
     * @brief Get the entity's width.
     * @return The entity's width.
     */
    virtual unsigned int getWidth() const
    {
    	return mSprite.GetSize().x;
    }

    /**
     * @brief Get the x position.
     * @return The x position.
     */
    virtual float getX() const
    {
    	return mSprite.GetPosition().x;
    }

    /**
     * @brief Get the y position.
     * @return The y position.
     */
    virtual float getY() const
    {
    	return mSprite.GetPosition().y;
    }

    /**
     * @brief Set the alpha of the entity.
     * @param a The alpha value.
     */
    virtual void setAlpha(unsigned int a)
    {
    	const sf::Color& c = mSprite.GetColor();
    	mSprite.SetColor(sf::Color(c.r, c.g, c.b, a));
    }

    /**
     * @brief Set the X position.
     * @param x The x position.
     */
    virtual void setX(float x)
    {
    	mSprite.SetX(x);
    }

    /**
     * @brief Set the Y position.
     * @param y The y position.
     */
    virtual void setY(float y)
    {
    	mSprite.SetY(y);
    }

	protected:
    // The image.
    sf::Sprite mSprite;
};

#endif /* IMAGEENTITY_HPP_ */
