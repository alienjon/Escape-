/*
 * AudioManager.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "AudioManager.hpp"

#include <stdexcept>

#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"

using std::list;
using std::map;
using std::runtime_error;
using std::string;

AudioManager::AudioManager()
{
}

sf::SoundBuffer& AudioManager::mGetSoundBuffer(const string& filename)
{
	// Get the requested sound buffer.
	map<string, sf::SoundBuffer>::iterator it = mSounds.find(filename);

	// If the sound buffer was not found, load it.
	if(it == mSounds.end())
	{
		mSounds[filename] = sf::SoundBuffer();
		if(!mSounds[filename].loadFromFile(filename))
			throw runtime_error("Error loading sound: " + filename);
		return mSounds[filename];
	}
	else
		return it->second;
}

void AudioManager::create()
{
    if(!mAudioManager)
        mAudioManager = new AudioManager;
}

float AudioManager::getMusicLevel()
{
	return mMusicLevel;
}

float AudioManager::getSoundLevel()
{
	return mSoundLevel;
}

void AudioManager::playMusic(const string& filename)
{
	if(!mAudioManager)
		create();

	if(!mAudioManager->mMusic.openFromFile(filename))
		ERROR("Unable to open music file '" + filename);
	else
	{
		if(Game::isDebug())
			LOG("Playing: " + filename);

		mAudioManager->mMusic.setVolume(AudioManager::getMusicLevel());
		mAudioManager->mMusic.setLoop(true);
		mAudioManager->mMusic.play();
	}
}

void AudioManager::playSound(const string& filename)
{
	if(!mAudioManager)
		create();

	// Clear any stopped sounds.
	list<list<sf::Sound>::iterator> toRemove;
	for(list<sf::Sound>::iterator it = mAudioManager->mPlayingSounds.begin(); it != mAudioManager->mPlayingSounds.end(); ++it)
	{
		if(it->getStatus() == sf::Sound::Stopped)
			toRemove.push_back(it);
	}
	for(list<list<sf::Sound>::iterator>::iterator it = toRemove.begin(); it != toRemove.end(); ++it)
		mAudioManager->mPlayingSounds.erase(*it);

	// Create a sound from the sound buffer.
	try
	{
		mAudioManager->mPlayingSounds.push_back(sf::Sound(mAudioManager->mGetSoundBuffer(filename)));
		mAudioManager->mPlayingSounds.back().setVolume(mSoundLevel);
		mAudioManager->mPlayingSounds.back().play();
	}
	catch(const runtime_error& e)
	{
		ERROR(e.what());
	}
}

void AudioManager::setMusicLevel(float level)
{
	if(!mAudioManager)
		create();

	// Set the level.
	mMusicLevel = (level > 100) ? 100 : level;

	// Set the music level.
	mAudioManager->mMusic.setVolume(mMusicLevel);
}

void AudioManager::setSoundLevel(float level)
{
	if(!mAudioManager)
		create();

	// Set the level.
	mSoundLevel = (level > 100) ? 100 : level;

	// Set the sound level.
	for(list<sf::Sound>::iterator it(mAudioManager->mPlayingSounds.begin()); it != mAudioManager->mPlayingSounds.end(); ++it)
		it->setVolume(mSoundLevel);
}

void AudioManager::terminate()
{
    delete mAudioManager;
    mAudioManager = 0;
}

AudioManager* AudioManager::mAudioManager = 0;
float AudioManager::mMusicLevel = 0;
float AudioManager::mSoundLevel = 0;
