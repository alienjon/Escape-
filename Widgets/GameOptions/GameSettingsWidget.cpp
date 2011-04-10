/*
 * GameSettingsWidget.cpp
 *
 *  Created on: Jun 30, 2010
 *      Author: the-saint
 */

#include "GameSettingsWidget.hpp"

#include <string>

#include "../../Engine/Logger.hpp"

using std::string;

const string GAMESETTINGS_OPENGL_GROUP = "OpenGL Group";
const string GAMESETTINGS_AUDIO_GROUP  = "Audio Group";

const unsigned int GAMESETTINGS_BUFFER = 20;

GameSettingsWidget::GameSettingsWidget() :
	mResolutionLabel("Resolution"),
	mOpenGLLabel("OpenGL Enabled"),
	mAudioStateLabel("Audio Enabled"),
	mVolumeLabel("Volume Level"),
	mOpenGLEnabled("Enabled", GAMESETTINGS_OPENGL_GROUP, false), // @todo If opengl is implemented, change this to true?  If not, then remove this entirely.
	mOpenGLDisabled("Disabled", GAMESETTINGS_OPENGL_GROUP, true),
	mAudioEnabled("Enabled", GAMESETTINGS_AUDIO_GROUP, true),
	mAudioDisabled("Disabled", GAMESETTINGS_AUDIO_GROUP, false),
	mVolume(0, 100)
{
	// Configure the widget itself.
	setOpaque(false);

	// Configure the internal widgets.
	mResolution.addActionListener(this);
	mOpenGLEnabled.addActionListener(this);
	mOpenGLDisabled.addActionListener(this);
	mAudioEnabled.addActionListener(this);
	mAudioDisabled.addActionListener(this);
	mVolume.addActionListener(this);
	add(&mResolutionLabel);
	add(&mResolution);
	add(&mOpenGLLabel);
	add(&mOpenGLEnabled);
	add(&mOpenGLDisabled);
	add(&mAudioStateLabel);
	add(&mAudioEnabled);
	add(&mAudioDisabled);
	add(&mVolumeLabel);
	add(&mVolume);
}

void GameSettingsWidget::action(const gcn::ActionEvent& event)
{
	if(event.getSource() == &mResolution)
	{
		Logger::log("Need to implement changing the resolution.");
	}
	else if(event.getSource() == &mOpenGLEnabled)
	{
		Logger::log("Need to implement enabling OpenGL.");
	}
	else if(event.getSource() == &mOpenGLDisabled)
	{
		Logger::log("Need to implement disabling OpenGL.");
	}
	else if(event.getSource() == &mAudioEnabled)
	{
		Logger::log("Need to implement enabling audio.");
	}
	else if(event.getSource() == &mAudioDisabled)
	{
		Logger::log("Need to implement disabling audio.");
	}
	else if(event.getSource() == &mVolume)
	{
		Logger::log("Need to implement volume changes.");
	}
}

void GameSettingsWidget::adjustSize()
{
	// Adjust the size of the internal widgets.
	mResolutionLabel.adjustSize();
	mOpenGLLabel.adjustSize();
	mAudioStateLabel.adjustSize();
	mVolumeLabel.adjustSize();
	mVolume.setSize(mOpenGLEnabled.getWidth() + mOpenGLDisabled.getWidth() + GAMESETTINGS_BUFFER, 20);

	// Set the positions.
	mResolutionLabel.setPosition(0, 0);
	mResolution.setPosition(0, mResolutionLabel.getY() + mResolutionLabel.getHeight());

	mOpenGLLabel.setPosition(0, mResolution.getY() + mResolution.getHeight() + GAMESETTINGS_BUFFER);
	mOpenGLEnabled.setPosition(0, mOpenGLLabel.getY() + mOpenGLLabel.getHeight());
	mOpenGLDisabled.setPosition(mOpenGLEnabled.getX() + mOpenGLEnabled.getWidth() + 10, mOpenGLEnabled.getY());

	mAudioStateLabel.setPosition(0, mOpenGLEnabled.getY() + mOpenGLEnabled.getHeight() + GAMESETTINGS_BUFFER);
	mAudioEnabled.setPosition(0, mAudioStateLabel.getY() + mAudioStateLabel.getHeight());
	mAudioDisabled.setPosition(mAudioEnabled.getX() + mAudioEnabled.getWidth() + 10, mAudioEnabled.getY());

	mVolumeLabel.setPosition(0, mAudioEnabled.getY() + mAudioEnabled.getHeight() + GAMESETTINGS_BUFFER);
	mVolume.setPosition(4, mVolumeLabel.getY() + mVolumeLabel.getHeight());
}
