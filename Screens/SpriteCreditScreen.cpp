///*
// * SpriteCreditScreen.cpp
// *
// *  Created on: Jun 24, 2009
// *      Author: alienjon
// */
//#include "SpriteCreditScreen.hpp"
//
//#include <stdexcept>
//
//#include "../Game/Game.hpp"
//#include "../main.hpp"
//
//using std::logic_error;
//
//SpriteCreditScreen::SpriteCreditScreen(const sf::Sprite& sprite, float time) :
//	mSprite(sprite),
//	mDisplayTime(time)
//{
//	// Set the sprite's position.
//	mSprite.SetPosition((mSprite.GetWidth() / 2) - (SCREEN_WIDTH / 2), (mSprite.GetHeight() / 2) - (SCREEN_HEIGHT / 2));
//}
//
//void SpriteCreditScreen::draw(sf::RenderWindow& renderer)
//{
//	renderer.Draw(mSprite);
//}
//
//void SpriteCreditScreen::handleInput(const Input& input)
//{
//	if(input.isKeyPressed(sf::Key::Space))
//	{
//		mDone = true;
//	}
//}
//
//void SpriteCreditScreen::load(GUI* gui)
//{
//	// @note Nothing to load for this screen.
//	(void)gui;
//
//    // Start the timer.
//    mTimer.Reset();
//}
//
//void SpriteCreditScreen::logic()
//{
//	// If the time has completed, the sprite is done.
//	if(mTimer.GetElapsedTime() >= mDisplayTime)
//		mDone = true;
//}
//
//void SpriteCreditScreen::unload()
//{
//}
//
//const unsigned int SpriteCreditScreen::mALPHA_RATE = 25;
