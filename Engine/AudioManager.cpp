/*
 * AudioManager.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "AudioManager.hpp"

#include <stdexcept>

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
		if(!mSounds[filename].LoadFromFile(filename))
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

//sf::Music AudioManager::getMusic(const string& filename)
//{
//	if(!mAudioManager)
//		create();
//
//	// Find/load the requested music file.
//	map<string, sf::Music>::iterator it = mAudioManager->mMusics.find(filename);
//
//	// If the music isn't found, load it.
//	if(it == mAudioManager->mMusics.end())
//	{
//		mAudioManager->mMusics[filename] = sf::Music();
//		if(!mAudioManager->mMusics[filename].OpenFromFile(filename))
//			throw runtime_error("Error loading music: " + filename);
//		return mAudioManager->mMusics[filename];
//	}
//	else
//		return it->second;
//}

void AudioManager::playSound(const string& filename)
{
	if(!mAudioManager)
		create();

	// Clear any stopped sounds.
	list<list<sf::Sound>::iterator> toRemove;
	for(list<sf::Sound>::iterator it = mAudioManager->mPlayingSounds.begin(); it != mAudioManager->mPlayingSounds.end(); ++it)
	{
		if(it->GetStatus() == sf::Sound::Stopped)
			toRemove.push_back(it);
	}
	for(list<list<sf::Sound>::iterator>::iterator it = toRemove.begin(); it != toRemove.end(); ++it)
		mAudioManager->mPlayingSounds.erase(*it);

	// Create a sound from the sound buffer.
	try
	{
		mAudioManager->mPlayingSounds.push_back(sf::Sound(mAudioManager->mGetSoundBuffer(filename)));
		mAudioManager->mPlayingSounds.back().Play();
	}
	catch(const runtime_error& e)
	{
		Logger::warn(e.what());
	}
}

void AudioManager::terminate()
{
    delete mAudioManager;
    mAudioManager = 0;
}

AudioManager* AudioManager::mAudioManager = 0;
