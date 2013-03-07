/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "../Engine/AudioManager.hpp"
#include "../Engine/FontManager.hpp"
#include "../Game/Game.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"
#include "../Engine/RendererContext.hpp"

using std::abs;
using std::runtime_error;
using std::string;
using std::vector;

using namespace boost::filesystem;

const unsigned int SCORE_COUNTER_INTERVAL = 25;
const unsigned int __TIME_MULTIPLIER__ = 1000;//@todo change time multiplier for difficulty levels? Laura found game a bit too hard, Dan a bit too easy?
//@fixme make the time multiplier be based on the difficulty

#include <iostream>
using namespace std;//@todo remove when done

GameScreen::GameScreen(unsigned int difficulty) : Screen(),
	mDifficulty(difficulty),
	mIsPaused(false),
	mLevel(0),
	mScore(0),
	mCounter(0),
	mOptionsWidget(0),
	mVideoOptionsWidget(0),
	mAudioOptionsWidget(0),
	mResetView(false)
{
	// Load all flac audio as background musics.
	path p("Audio/");

	try
	{
		// Make sure that Audio/ exists and is a directory.
		// NOTE: The following code is modified from the boost::filesystem tutorials website.
		if(exists(p) && is_directory(p))
		{
			// Create a vector of items within the directory and populate it.
			vector<path> v;
			copy(directory_iterator(p), directory_iterator(), back_inserter(v));

			for(vector<path>::const_iterator it(v.begin()); it != v.end(); ++it)
				if(it->extension() == ".flac")
					mBackMusicVector.push_back(it->native());
		}
		else
			ERROR("Audio directory not found.  No background music will be played.");
	}
	catch(filesystem_error& e)
	{
		ERROR(e.what());
	}

	//@todo remove when GUI system is implemented
	if(!mFont.loadFromFile("Fonts/VeraMono.ttf"))
		ERROR("GameScreen::GameScreen() -> Unable to load font.");

	/* Load the in game menus */
	mOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameOptions.layout"));
	mOptionsWidget->setSizingEnabled(false);
	mOptionsWidget->setVisible(false);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mOptionsWidget);

	mVideoOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameVideoOptions.layout"));
	mVideoOptionsWidget->setSizingEnabled(false);
	mVideoOptionsWidget->setVisible(false);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mVideoOptionsWidget);

	mAudioOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameAudioOptions.layout"));
	mAudioOptionsWidget->setSizingEnabled(false);
	mAudioOptionsWidget->setVisible(false);
	static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume"))->setMaxValue(100.f);
	static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume"))->setClickStep(5.f);
	static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume"))->setMaxValue(100.f);
	static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume"))->setClickStep(5.f);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mAudioOptionsWidget);

	mUpdateWidgetPositions(); // Set the initial positions.

	// Subscribe to the various widget interfaces.
	mOptionsWidget->getChild("InGameOptionsMenu/ResumeButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerCloseOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/VideoButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerShowVideoOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/AudioButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerShowAudioOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/MainMenuButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerMainMenu, this));
	mVideoOptionsWidget->getChild("InGameVideoOptions/CloseButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerCloseVideoOptions, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/CloseButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerCloseAudioOptions, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume")->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&GameScreen::_handlerUpdateMusicTextLevels, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume")->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&GameScreen::_handlerUpdateSoundTextLevels, this));
}

GameScreen::~GameScreen()
{
	// In the event that the game crashes before a level is loaded, this will segfault without a check.
	if(mLevel)
	{
		mLevel->removeChangeScoreListener(this);
		mLevel->removeTimeChangeListener(this);
		delete mLevel;
	}

	for(list<CEGUI::ListboxTextItem*>::const_iterator it(mResolutionOptions.begin()); it != mResolutionOptions.end(); ++it)
		delete *it;
}

void GameScreen::mUpdateWidgetPositions()
{
	mOptionsWidget->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.25f, 0)));
	mOptionsWidget->setSize(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.3f, 0)));
	mVideoOptionsWidget->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.25f, 0)));
	mVideoOptionsWidget->setSize(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.45f, 0)));
	mAudioOptionsWidget->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.25f, 0)));
	mAudioOptionsWidget->setSize(CEGUI::UVector2(CEGUI::UDim(0.35f, 0),CEGUI::UDim(0.45f, 0)));
}

bool GameScreen::_handlerShowAudioOptions(const CEGUI::EventArgs& eArgs)
{
	mOptionsWidget->setVisible(false);
	mAudioOptionsWidget->setVisible(true);
	return true;
}

bool GameScreen::_handlerCloseAudioOptions(const CEGUI::EventArgs& eArgs)
{
	mAudioOptionsWidget->setVisible(false);
	mOptionsWidget->setVisible(true);
	AudioManager::setMusicLevel(int(static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume"))->getCurrentValue()));
	AudioManager::setSoundLevel(int(static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume"))->getCurrentValue()));
	return true;
}

bool GameScreen::_handlerCloseOptions(const CEGUI::EventArgs& eArgs)
{
	mIsPaused = false; // Unpause the game.
	mTimerWidget.unpause(); // Unpause the game timer.
	mOptionsWidget->setVisible(false); // Hide the options widget.
	distributeEvent(ACTION_HIDECURSOR); // Hide the cursor.
	return true;
}

bool GameScreen::_handlerCloseVideoOptions(const CEGUI::EventArgs& eArgs)
{
	mVideoOptionsWidget->setVisible(false);
	mOptionsWidget->setVisible(true);
	if(!mContextInterface)
		ERROR("GameScreen::_handlerCloseVideoOptions(const CEGUI::EventArgs&) -> Context interface not set.  Video options not updated.");
	else
	{
		// Get the current context to update.
		RendererContext s = mContextInterface->getContext();

		// Set the resolution.
		//@fixme Can this be cleaned up? (With find_if, maybe?)
		switch(static_cast<CEGUI::Combobox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/Resolution"))->getSelectedItem()->getID())
		{
			case 0:
			{
				s.mVideoMode.width = 640;
				s.mVideoMode.height= 480;
				break;
			}
			case 2:
			{
				s.mVideoMode.width = 1024;
				s.mVideoMode.height= 768;
				break;
			}
			case 3:
			{
				s.mVideoMode.width = 1280;
				s.mVideoMode.height= 1024;
				break;
			}
			case 4:
			{
				s.mVideoMode.width = 1366;
				s.mVideoMode.height= 768;
				break;
			}
			case 5:
			{
				s.mVideoMode.width = 1440;
				s.mVideoMode.height= 900;
				break;
			}
			case 6:
			{
				s.mVideoMode.width = 1920;
				s.mVideoMode.height= 1080;
				break;
			}
			default:
			{
				s.mVideoMode.width = 800;
				s.mVideoMode.height= 600;
				break;
			}
		}
		// Set the BPP.
		if(static_cast<CEGUI::RadioButton*>(mVideoOptionsWidget->getChild("InGameVideoOptions/16bpp"))->isSelected())
			s.mVideoMode.bitsPerPixel = 16;
		else if(static_cast<CEGUI::RadioButton*>(mVideoOptionsWidget->getChild("InGameVideoOptions/24bpp"))->isSelected())
			s.mVideoMode.bitsPerPixel = 24;
		else
			s.mVideoMode.bitsPerPixel = 32;

		// Set the vertical sync.
		s.mVerticalSync = static_cast<CEGUI::Checkbox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/VerticalSync"))->isSelected();

		// Set the antialiasing.
		s.mContextSettings.antialiasingLevel = (static_cast<CEGUI::Checkbox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/AntiAliasing"))->isSelected()) ? 8 : 0;

		// Update the context.
		mContextInterface->updateContext(s);

		// Update the widget positions.
		mUpdateWidgetPositions();
	}

	return true;
}

bool GameScreen::_handlerMainMenu(const CEGUI::EventArgs& eArgs)//@todo implement main menu
{
	distributeEvent(ACTION_QUIT);
	LOG("Main menu not yet implemented.");
	return true;
}

bool GameScreen::_handlerShowVideoOptions(const CEGUI::EventArgs& eArgs)
{
	mOptionsWidget->setVisible(false);
	mVideoOptionsWidget->setVisible(true);
	return true;
}

bool GameScreen::_handlerUpdateMusicTextLevels(const CEGUI::EventArgs& eArgs)
{
	mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolumeLevel")->setText(toString(int(static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume"))->getCurrentValue())));
	return true;
}

bool GameScreen::_handlerUpdateSoundTextLevels(const CEGUI::EventArgs& eArgs)
{
	mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolumeLevel")->setText(toString(int(static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume"))->getCurrentValue())));
	return true;
}

void GameScreen::changeScore(int change)
{
	mCounter += change;
//	mScoreLabel.setCaption("Score: " + toString(mScore));
	mScoreDisplay.setString("Score: " + toString(mScore));
}

void GameScreen::draw(sf::RenderWindow& renderer)
{
	// If resetting the view, reset it.
	if(mResetView)
	{
		mCamera = renderer.getDefaultView();
		mResetView = false;
	}

	// Everything on the level is relative to the viewport.
	renderer.setView(mCamera);

    // Draw any screen objects.
    mLevel->draw(renderer);

    // Return the view.
    renderer.setView(renderer.getDefaultView());

    //@fixme Draw the temporary widgets.
    //@note These have to be done after setting the view because they are in the GUI.
    mTimerWidget.draw(renderer);
    renderer.draw(mScoreDisplay);
}

void GameScreen::eventOccurred(const string& eventId)
{
	string::size_type pos = 0;
	string keyword = extractDataLine(eventId, pos, DELIMITER);
	//@fixme need to re-implement gui here
/*	if(false)//@fixme need to create an eventId for completing the level: event.getSource() == &mLevelCompleteWidget)
	{
		// If the old level completed, then load the next level.
		if(mLevel->isDone())
		{
			// Unload the current level.
			mLevel->removeEventListener(this);
			mLevel->removeChangeScoreListener(this);
			mLevel->removeTimeChangeListener(this);
			delete mLevel;

			// Increase the difficulty and go to the next level.
			mLevel = new Level(++mDifficulty, mPlayer);
			mLevel->addEventListener(this);
			mLevel->addChangeScoreListener(this);
			mLevel->addTimeChangeListener(this);

		    // Reset the view.
		    mResetView = true;//@fixme this isn't working.  Make sure the view is reset when a new level is loaded.

			// Make sure the game is not paused.
			mTimerWidget.stop();
			mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);//@todo remove when done
			mIsPaused = false;
		}
		// If the old level didn't complete, then the level was lost.
		else
		{
//			setActionEventId(ACTION_TO_MAINMENU);//@todo implement main menu.
//			distributeActionEvent();
			mDone = true;
		}
	}
	else if(keyword == GAMEOPTIONS_RESUME)
	{
		mIsPaused = false;
		mTimerWidget.unpause();
		distributeEvent(ACTION_HIDECURSOR);
	}
	else if(keyword == GAMEOPTIONS_MAINMENU)
	{
		distributeEvent(ACTION_TO_MAINMENU);
		mDone = true;
	}
	else if(keyword == GAMEOPTIONS_EXIT)
	{
		distributeEvent(ACTION_QUIT);
		mDone = true;
	}
	// Now check for the id's.
	else*/ if(keyword == ACTION_QUIT)
		mDone = true;
	else if(keyword == ACTION_TO_MAINMENU)
	{
		distributeEvent(ACTION_TO_MAINMENU);
		mDone = true;
	}
	else if(keyword == ACTION_PAUSE)
		mIsPaused = true;
	else if(keyword == ACTION_UNPAUSE)
		mIsPaused = false;
}

bool GameScreen::handleInput(const sf::Event& event)
{
	// Open the options menu.
	// @todo implement options menu
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		if(!mOptionsWidget->isVisible())
		{
			mIsPaused = true; // Pause the game.
			mTimerWidget.pause(); // Pause the game timer.
			mOptionsWidget->setVisible(true); // Show the options widget.
			distributeEvent(ACTION_SHOWCURSOR); // Show the cursor.
		}
		else
		{
			_handlerCloseOptions(CEGUI::EventArgs());
		}
	}

	// Have the player perform any input.
	mPlayer.handleInput(event);

	return true;
}

void GameScreen::load(const sf::View& view)
{
    // Hide the cursor.
    distributeEvent(ACTION_HIDECURSOR);

    /* Set the options settings */

    // Set the default video options if the context interface is present.
	if(!mContextInterface)
		ERROR("GameScreen::GameScreen() -> mContextInterface not set.  Not setting video options.");
	else
	{
		// Load/set the resolution options.
		//@fixme This feels bloated, is there a better way of approaching this? (maybe a find_if?)
		CEGUI::Combobox* cbox = static_cast<CEGUI::Combobox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/Resolution"));
		cbox->setReadOnly(true);
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("640x480", 0));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("800x600", 1));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("1024x768", 2));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("1280x1024", 3));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("1366x768", 4));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("1440x900", 5));
		mResolutionOptions.push_back(new CEGUI::ListboxTextItem("1920x1080", 6));
		for(list<CEGUI::ListboxTextItem*>::const_iterator it(mResolutionOptions.begin()); it != mResolutionOptions.end(); ++it)
		{
			(*it)->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");//@todo needed?
			cbox->addItem(*it);
		}
		cbox->setHeight(CEGUI::UDim(0.75f, 0));

		switch(mContextInterface->getContext().mVideoMode.width)
		{
			case 640:
			{
				cbox->setItemSelectState((unsigned int)0, true);
				break;
			}
			case 1024:
			{
				cbox->setItemSelectState((unsigned int)2, true);
				break;
			}
			case 1280:
			{
				cbox->setItemSelectState((unsigned int)3, true);
				break;
			}
			case 1366:
			{
				cbox->setItemSelectState((unsigned int)4, true);
				break;
			}
			case 1440:
			{
				cbox->setItemSelectState((unsigned int)5, true);
				break;
			}
			case 1920:
			{
				cbox->setItemSelectState((unsigned int)6, true);
				break;
			}
			default:
			{
				cbox->setItemSelectState((unsigned int)1, true);
				break;
			}
		}

		// Load/set the bitdepths.
		switch(mContextInterface->getContext().mContextSettings.depthBits)
		{
			case 16:
			{
				static_cast<CEGUI::RadioButton*>(mVideoOptionsWidget->getChild("InGameVideoOptions/16bpp"))->setSelected(true);
				break;
			}
			case 24:
			{
				static_cast<CEGUI::RadioButton*>(mVideoOptionsWidget->getChild("InGameVideoOptions/24bpp"))->setSelected(true);
				break;
			}
			default:
			{
				static_cast<CEGUI::RadioButton*>(mVideoOptionsWidget->getChild("InGameVideoOptions/32bpp"))->setSelected(true);
				break;
			}
		}

		// Load/set the v-sync.
		static_cast<CEGUI::Checkbox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/VerticalSync"))->setSelected(mContextInterface->getContext().mVerticalSync);

		// Load/set anti-aliasing.
		static_cast<CEGUI::Checkbox*>(mVideoOptionsWidget->getChild("InGameVideoOptions/AntiAliasing"))->setSelected(mContextInterface->getContext().mContextSettings.antialiasingLevel ? 16 : 0);

		// Set the initial audio settings.
		mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolumeLevel")->setText(toString(AudioManager::getMusicLevel()));
		static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume"))->setCurrentValue(float(AudioManager::getMusicLevel()));
		mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolumeLevel")->setText(toString(AudioManager::getSoundLevel()));
		static_cast<CEGUI::Slider*>(mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume"))->setCurrentValue(float(AudioManager::getSoundLevel()));

	}

    // Setup the in-game options menu.
    //@todo implement options menu
//    mOptionsMenu.setVisible(false);
//    mOptionsMenu.setSize(mBase.getWidth(), mBase.getHeight());
//    mOptionsMenu.adjustInternals();
//    mBase.add(&mOptionsMenu, 0, 0);

    // Add the menu bar.
    //@todo implement score widget
    mScoreDisplay.setFont(mFont);
    mScoreDisplay.setString("Score: 0");
    mScoreDisplay.setCharacterSize(18);
    mScoreDisplay.setColor(sf::Color::Magenta);
    mScoreDisplay.setStyle(sf::Text::Bold);
    mScoreTimer.start();
    mScoreDisplay.setPosition(0, view.getSize().y - mScoreDisplay.getLocalBounds().height - 2);
//	mScoreLabel.setFont(FontManager::getGCNFont(FONT_DEFAULT));
//	mScoreLabel.setCaption("Score: 0");
//	mScoreLabel.adjustSize();
//	mScoreTimer.start();
//    mBase.add(&mScoreLabel, 0, mBase.getHeight() - mScoreLabel.getHeight());
//    addTimeChangeListener(&mTimerWidget);
//    mBase.add(&mTimerWidget, mBase.getWidth() - mTimerWidget.getWidth(), mBase.getHeight() - mTimerWidget.getHeight());

    // Add the level complete widget.
    //@todo implement level complete
//    mLevelCompleteWidget.setVisible(false);
//    mBase.add(&mLevelCompleteWidget);

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer);
    mLevel->addChangeScoreListener(this);
    mLevel->addTimeChangeListener(this);

    // Reset the view.
    mResetView = true;

    // Restart the timer
    //@todo re-implement new widget
    mTimerWidget.stop();
    mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
    mTimerWidget.setPosition(view.getSize().x - mTimerWidget.getWidth(), view.getSize().y - mTimerWidget.getHeight() - 2);

	// Pick a random background music.
	string music = mBackMusicVector.at(random(0, int(mBackMusicVector.size() - 1)));
	if(!mBackMusic.openFromFile(music))
		ERROR("Unable to open music file '" + music);
	else
	{
		if(Game::isDebug())
			LOG("Playing: " + music);
		mBackMusic.play();
		mBackMusic.setLoop(true);;
	}
}

void GameScreen::logic(int delta)
{
	// @todo temporary hack for the timer widget logic (need to implement full gui)
	mTimerWidget.logic();

	// Update the score.
	if(mCounter != 0 && mScoreTimer.getTime() >= SCORE_COUNTER_INTERVAL)
	{
		// Only increment the score by 1, but determine the direction.
		int sign = (mCounter != 0) ? mCounter / abs(mCounter) : 0;

		// Increment the score.
		mScore = (sign < 0 && mScore == 0) ? 0 : mScore + sign;

		// Set the score.
		//@todo implement score label widget
//		mScoreLabel.setCaption("Score: " + toString(mScore));
		mScoreDisplay.setString("Score: " + toString(mScore));

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}

	// If time is up, then the player has lost...
	//@todo implement level complete widget
//	if(mTimerWidget.getTime() == 0 && !mLevel->isDone() && !mLevelCompleteWidget.isVisible())
//	{
//		// Pause the game.
//		mTimerWidget.stop();
//		mIsPaused = true;
//
//		// Display the level complete widget, but don't add any bonuses.
//		double bonusMod = 0;
//		unsigned int bonus = 0;
//		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
//		mLevelCompleteWidget.display("LEVEL FAILED", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);//@todo remove when done
//		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
//	}
//	// ... or if the next level should be loaded.
//	else if(mLevel->isDone() && !mLevelCompleteWidget.isVisible())
//	{
//		// Pause the game.
//		mTimerWidget.pause();
//		mIsPaused = true;
//
//		// Add the rest of the counter to the score and set the final score.
//		mScore = (mScore + mCounter < 0) ? 0 : mScore + mCounter;
//		mCounter = 0;
//
//		// Display the level complete widget.
//		double bonusMod = (mDifficulty / 10.0) + 1;
//		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
//		unsigned int bonus = (timeBonus) * bonusMod;
//		mLevelCompleteWidget.display("LEVEL COMPLETE", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
//		mScoreLabel.setCaption(toString(mScore += bonus));
//		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
//	}

    // Only do game logic if the game is not paused.
    if(!mIsPaused)
		mLevel->logic(mCamera, delta);
}
