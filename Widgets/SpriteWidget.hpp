///*
// * SpriteWidget.hpp
// *
// *  Created on: Jun 26, 2009
// *      Author: alienjon
// */
//#ifndef SPRITEWIDGET_HPP_
//#define SPRITEWIDGET_HPP_
//
//#include "../guichan.hpp"
//
//#include "../Listeners/AnimationCycleListener.hpp"
//
///**
// * @brief A sprite widget is a widget to show an animation (sprite)
// *
// * A sprite widget is similar to a gcn::Icon in that it displays an
// * image via the gcn::Widget interface but instead acts on a sprite,
// * thereby allowing an animation in widget form.
// */
//class SpriteWidget : public gcn::Widget
//{
//    public:
//    /**
//     * @brief Create an empty sprite widget.
//     */
//    SpriteWidget();
//
//    /**
//     * @brief Similar to an gcn::Icon except it takes a sprite.
//     * @param sprite The sprite to display.
//     */
//    SpriteWidget(const sf::Sprite& sprite);
//
//    /**
//     * @brief Add an animation cycle listener.
//     * @param listener The listener to add.
//     */
//    void addAnimationCycleListener(AnimationCycleListener* listener);
//
//    /**
//     * @brief Draw the sprite.
//     * @param graphics The graphics object with which to draw the sprite.
//     */
//    virtual void draw(gcn::Graphics* graphics);
//
//    /**
//     * @brief Perform logic.
//     */
//    virtual void logic();
//
//    /**
//     * @brief Remove an animation cycle listener.
//     * @param listener The listener to remove.
//     */
//    void removeAnimationCycleListener(AnimationCycleListener* listener);
//
//    /**
//     * @brief Set the displaying sprite.
//     * @param sprite The sprite to set.
//     */
//    void setSprite(const Sprite& sprite);
//
//    protected:
//    // The sprite.
//    sf::Sprite mSprite;
//};
//
//#endif /* SPRITEWIDGET_HPP_ */
