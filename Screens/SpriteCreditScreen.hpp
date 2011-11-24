///*
// * SpriteCreditScreen.hpp
// *
// *  Created on: Jun 24, 2009
// *      Author: alienjon
// */
//#ifndef SPRITECREDITSCREEN_HPP_
//#define SPRITECREDITSCREEN_HPP_
//
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <string>
//
//#include "../Game/GUI.hpp"
//#include "../Screens/Screen.hpp"
//
///**
// * @brief A screen that only displays a single sprite and is intended for credits.
// */
//class SpriteCreditScreen : public Screen
//{
//    public:
//    /**
//     * @brief Displays a sprite on the screen for a period of time.
//     * @param sprite This will show a single framed animation (a single image).
//     * @param time The time to display the screen (in seconds).
//     */
//    SpriteCreditScreen(const sf::Sprite& surface, float time);
//
//    /**
//     * @brief Input handling.
//     * @param input The input.
//     * @note Should be used for non-gui input.
//     */
//    virtual void handleInput(const Input& input);
//
//    /**
//     * @brief The logic function.
//     */
//    virtual void logic();
//
//    /**
//     * @brief Draw the screen.
//     * @param renderer The graphics object with which to draw.
//     */
//    virtual void draw(sf::RenderWindow& renderer);
//
//    /**
//     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
//     * @param gui The gui object.
//     */
//    virtual void load(GUI* gui);
//
//    /**
//     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
//     */
//    virtual void unload();
//
//    protected:
//    // The widget to display the image.
//    sf::Sprite mSprite;
//
//    // The timer for the screen's various events.
//    sf::Clock mTimer;
//
//    // The time to display the screen.
//    unsigned int mDisplayTime;
//};
//
//#endif /* SPRITECREDITSCREEN_HPP_ */
