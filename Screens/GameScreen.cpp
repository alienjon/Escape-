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
#include "../Game/Game.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"
#include "../Engine/RendererContext.hpp"

using std::abs;
using std::list;
using std::runtime_error;
using std::string;
using std::vector;

using namespace boost::filesystem;

GameScreen::GameScreen(unsigned int level, Game::Difficulty difficulty) : Screen(),
	mDifficulty(level),
	mTimeMultiplier(0),
	mIsPaused(false),
	mLevel(0),
	mOptionsWidget(0),
	mVideoOptionsWidget(0),
	mAudioOptionsWidget(0),
	mLevelComplete(0),
	mLevelCompleteText(0),
	mResetView(false)
{
	// Determine the time multiplier.
	switch(difficulty)
	{
		case Game::EASY:
		{
			mTimeMultiplier = 1250;
			break;
		}
		case Game::HARD:
		{
			mTimeMultiplier = 800;
			break;
		}
		default:
			mTimeMultiplier = 1000; break;
	}

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

	/* Load the in game widgets */
	mOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameOptions.layout"));
	mOptionsWidget->setVisible(false);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mOptionsWidget);

	mVideoOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameVideoOptions.layout"));
	mVideoOptionsWidget->setVisible(false);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mVideoOptionsWidget);

	mAudioOptionsWidget = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("InGameAudioOptions.layout"));
	mAudioOptionsWidget->setVisible(false);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mAudioOptionsWidget);

	mLevelComplete = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().loadWindowLayout("LevelComplete.layout"));
	mLevelComplete->setVisible(false);
	mLevelCompleteText = mLevelComplete->getChild("LevelCompleteWidget/Text");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(mLevelComplete);

	// Subscribe to the various widget interfaces.
	mOptionsWidget->getChild("InGameOptionsMenu/ResumeButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerCloseOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/VideoButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerShowVideoOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/AudioButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerShowAudioOptions, this));
	mOptionsWidget->getChild("InGameOptionsMenu/MainMenuButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerMainMenu, this));
	mVideoOptionsWidget->getChild("InGameVideoOptions/ApplyButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerApplyVideoOptions, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/ApplyButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerApplyAudioOptions, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/MusicVolume")->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&GameScreen::_handlerUpdateMusicTextLevels, this));
	mAudioOptionsWidget->getChild("InGameAudioOptions/SoundVolume")->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&GameScreen::_handlerUpdateSoundTextLevels, this));
	mLevelComplete->getChild("LevelCompleteWidget/MainMenuButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameScreen::_handlerMainMenu, this));

	// Configure any non-CEGUI widgets.
	mTimerWidget.addTimeUpListener(this);
    addTimeChangeListener(&mTimerWidget);
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

	// Remove any needed listeners.
	mTimerWidget.removeTimeUpListener(this);
}

bool GameScreen::_handlerShowAudioOptions(const CEGUI::EventArgs& eArgs)
{
	mOptionsWidget->setVisible(false);
	mAudioOptionsWidget->setVisible(true);
	return true;
}

bool GameScreen::_handlerApplyAudioOptions(const CEGUI::EventArgs& eArgs)
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

bool GameScreen::_handlerApplyVideoOptions(const CEGUI::EventArgs& eArgs)
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
	}

	return true;
}

bool GameScreen::_handlerMainMenu(const CEGUI::EventArgs& eArgs)//@todo implement main menu
{
	distributeEvent(ACTION_QUIT);
	mDone = true;
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
	mScoreWidget.changeScore(change);
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

    //@note Widgets have to be done after setting the view because they are in the GUI.
    mTimerWidget.draw(renderer);
    mScoreWidget.draw(renderer);
}

void GameScreen::eventOccurred(const string& eventId)
{
	string::size_type pos = 0;
	string keyword = extractDataLine(eventId, pos, DELIMITER);

	// Check for the id's.
	if(keyword == ACTION_PAUSE)
		mIsPaused = true;
	else if(keyword == ACTION_UNPAUSE)
		mIsPaused = false;
}

bool GameScreen::handleInput(const sf::Event& event)
{
	// Open the options menu.
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
			cbox->addItem(*it);
		}
		cbox->setHeight(CEGUI::UDim(0.75f, 0));

		switch(mContextInterface->getContext().mVideoMode.width)
		{
			case 640:
			{
				cbox->setItemSelectState((std::size_t)0, true);
				break;
			}
			case 1024:
			{
				cbox->setItemSelectState((std::size_t)2, true);
				break;
			}
			case 1280:
			{
				cbox->setItemSelectState((std::size_t)3, true);
				break;
			}
			case 1366:
			{
				cbox->setItemSelectState((std::size_t)4, true);
				break;
			}
			case 1440:
			{
				cbox->setItemSelectState((std::size_t)5, true);
				break;
			}
			case 1920:
			{
				cbox->setItemSelectState((std::size_t)6, true);
				break;
			}
			default:
			{
				cbox->setItemSelectState((std::size_t)1, true);
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

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer);
    mLevel->addChangeScoreListener(this);
    mLevel->addTimeChangeListener(this);

    // Reset the view.
    mResetView = true;

    // Load widget information.
    mTimerWidget.stop();
    mTimerWidget.start(mLevel->getMap().getComplexity() * mTimeMultiplier);
    mTimerWidget.setPosition(view.getSize().x - mTimerWidget.getWidth(), view.getSize().y - mTimerWidget.getHeight() - 2);
    mScoreWidget.setPosition(0, view.getSize().y - mScoreWidget.getHeight());

	// Pick a random background music.
	AudioManager::playMusic(mBackMusicVector.at(random(0, int(mBackMusicVector.size() - 1))));
}

void GameScreen::logic(int delta)
{
	// Perform widget logic.
	mTimerWidget.logic();
	mScoreWidget.logic();

	// If the level completed then display the score.
	if(mLevel->isDone())
	{
		// Pause the game.
		mTimerWidget.pause();
		mIsPaused = true;

		// Add the rest of the counter to the score and set the final score.
		mScoreWidget.setScore(mScoreWidget.getScore() + mScoreWidget.getCounter());

		// Display the level complete widget.
		double bonusMod = (mDifficulty / 10.0) + 1;
		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
		unsigned int bonus = (timeBonus) * bonusMod;

		// Display the level complete widget, but don't add any bonuses.
		string txt =
				string("LEVEL COMPLETED\n\n") +
				string("Time Remaining: ") + toString(mTimerWidget.getTime()) + "\n" +
				string("Maze Complexity: ") + toString(mLevel->getMap().getComplexity()) + "\n" +
				string("Difficulty: ") + toString(mDifficulty) + "\n" +
				string("Base Score: ") + toString(mScoreWidget.getScore()) + "\n" +
				string("Bonus Score: ") + toString(bonus) + "\n" +
				string("Total Score: ") + toString(mScoreWidget.getScore());
		mLevelCompleteText->setText(txt);
//@todo Need to implement the level finishing when the player collides with the door while holding the key
		// Show the cursor and the widget.
		distributeEvent(ACTION_SHOWCURSOR);
		mLevelComplete->setVisible(true);
	}

    // Only do game logic if the game is not paused.
    if(!mIsPaused)
		mLevel->logic(mCamera, delta);
}

void GameScreen::timeUp()
{
	// Pause the game.
	mTimerWidget.stop();
	mIsPaused = true;

	// Display the level complete widget, but don't add any bonuses.
	string txt =
			string("LEVEL FAILED\n\n") +
			string("Time Remaining: ") + toString(mTimerWidget.getTime()) + "\n" +
			string("Maze Complexity: ") + toString(mLevel->getMap().getComplexity()) + "\n" +
			string("Difficulty: ") + toString(mDifficulty) + "\n" +
			string("Base Score: ") + toString(mScoreWidget.getScore()) + "\n" +
			string("Bonus Score: 0\n") +
			string("Total Score: ") + toString(mScoreWidget.getScore());
	mLevelCompleteText->setText(txt);

	// Show the cursor and the widget.
	distributeEvent(ACTION_SHOWCURSOR);
	mLevelComplete->setVisible(true);
}
