/*
 * AudioManager.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "AudioManager.hpp"

#include <stdexcept>

#include "SDL/SDL.h"

#include "../Engine/Logger.hpp"

using std::list;
using std::runtime_error;
using std::string;

const string AUDIO_PREFIX = "Audio/";

AudioManager::AudioManager()
{
    // Initialize the audio.
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1)
    {
       Logger::log(string("SDL failed to initialize audio: ") + SDL_GetError());
    }

    // Now, open the audio device.
    if(Mix_OpenAudio(mFrequency, mFormat, mChannels, mChunkSize))
    {
      Logger::log(string("Unable to open the audio device: ") + SDL_GetError());
    }
    else
    {
        Logger::log("Audio initialization successful.");
    }

    // When sounds (not music) plays, tell some listeners.
    Mix_ChannelFinished(AudioManager::mPushSoundStopped);
}

AudioManager::~AudioManager()
{
    // Close the audio device.
    Mix_CloseAudio();
}

void AudioManager::mPushSoundStopped(int channel)
{
	for(list<SoundStoppedListener*>::iterator it = AudioManager::mSoundStoppedListeners.begin(); it != AudioManager::mSoundStoppedListeners.end(); ++it)
	{
		(*it)->soundStopped(channel);
	}
}

void AudioManager::addSoundStoppedListener(SoundStoppedListener* listener)
{
	AudioManager::mSoundStoppedListeners.push_back(listener);
}

void AudioManager::create()
{
    if(!mAudioManager)
    {
        mAudioManager = new AudioManager;
    }
}

void AudioManager::playMusic(const std::string& filename, int loops, unsigned int fadeIn)
{
	// Create the full filename.
	string music_file = AUDIO_PREFIX + filename;

    // Look for the resource, if it can't be found, then load the music.
    MusicCollection::iterator it = mAudioManager->mMusicCollection.find(music_file);
    Mix_Music* song = 0;
    if(it == mAudioManager->mMusicCollection.end())
    {
    	song = Mix_LoadMUS(music_file.c_str());

    	// If the song failed to load, then error and don't play anything.
    	if(!song)
    	{
    		Logger::error("Unable to load music.  '" + music_file + "' does not exist!");
    		return;
    	}

    	mAudioManager->mMusicCollection[music_file] = song;
    }
    else
    {
    	song = it->second;
    }

	// Stop playing the current song (can only play one music piece at a time)
	stopMusic();

	// Play the music.
	Mix_FadeInMusic(song, loops, fadeIn);
}

int AudioManager::playSound(const std::string& filename, int loops)
{
	// Create the full filename.
	string sound_file = AUDIO_PREFIX + filename;

    // Look for the resource, if it can't be found, then load the sound clip.
    SoundCollection::iterator it = mAudioManager->mSoundCollection.find(sound_file);
    Mix_Chunk* sound = 0;
    if(it == mAudioManager->mSoundCollection.end())
    {
    	// Load and check the sound.
        sound = Mix_LoadWAV(sound_file.c_str());
    	if(!sound)
    	{
    		Logger::error("Unable to load sound.  '" + sound_file + "' does not exist!");
    		return -1;
    	}

        mAudioManager->mSoundCollection[sound_file] = sound;
    }
    else
    {
    	sound = it->second;
    }

    return Mix_PlayChannel(-1, sound, loops);
}

void AudioManager::removeSoundStoppedListener(SoundStoppedListener* listener)
{
	AudioManager::mSoundStoppedListeners.remove(listener);
}

void AudioManager::stopMusic(unsigned int fadeOut)
{
    Mix_FadeOutMusic(fadeOut);
}

void AudioManager::stopSound(int channel)
{
    Mix_HaltChannel(channel);
}

void AudioManager::terminate()
{
    delete mAudioManager;
    mAudioManager = 0;
}

AudioManager* AudioManager::mAudioManager = 0;

list<SoundStoppedListener*> AudioManager::mSoundStoppedListeners;

int AudioManager::mFrequency = 44100;
Uint16 AudioManager::mFormat = AUDIO_S16SYS;
int AudioManager::mChannels  = 2;
int AudioManager::mChunkSize = 4096;
