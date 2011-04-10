/*
 * AudioManager.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include <list>
#include <map>
#include <string>

#include "SDL/SDL_mixer.h"

#include "../Listeners/SoundStoppedListener.hpp"

/**
 * @brief A class that manages both music and sound effects.
 *
 * @note Unline images, audio is loaded dynamically.  From the little I've used of SDL_mixer so far, it seems as though
 * opening audio files is much quicker, so to make things simply a user only needs to tell the manager the audio file to play,
 * whether it is sound or background music, and the manager will load that file for use throughout that running of the game.
 */
class AudioManager
{
    public:
    virtual ~AudioManager();

    /**
     * @brief Add a SoundStoppedListener.
     * @param listener The listener to add.
     */
    static void addSoundStoppedListener(SoundStoppedListener* listener);

    /**
     * @brief Create the audio manager.
     */
    static void create();

    /**
     * @brief Play the requested music file.
     * @param filename The filename of the music to play.
     * @param loops The number of times to play the music (default is 0, or infinite)
     * @param fadein The number of ms to fade in the music.
     */
    static void playMusic(const std::string& filename, int loops = 0, unsigned int fadeIn = 0);

    /**
     * @brief Play the requested sound file.
     * @param filename The filename of the sound file to play.
     * @param loops The number of times to play the sound (default is 0 or only once)
     * @return The channel of the playing sound (in case I need to stop it later)
     */
    static int playSound(const std::string& filename, int loops = 0);

    /**
     * @brief Remove a sound loop listener.
     * @param listener The listener to remove.
     */
    static void removeSoundStoppedListener(SoundStoppedListener* listener);

    /**
     * @brief Stop playing music.
     * @param fadeout The fadeout time for the music.
     */
    static void stopMusic(unsigned int fadeOut = 0);

    /**
     * @brief Stop playing the requested sound.
     * @param channel The channel of the sound to stop.
     * @note Pass -1 to stop all sounds.
     */
    static void stopSound(int channel);

    /**
     * @brief Delete the manager.
     */
    static void terminate();

    protected:
    /**
     * @brief This method tells the listeners that a sound stopped playing at the provided channel.
     * @param channel The channel at which the sound stopped playing.
     */
    static void mPushSoundStopped(int channel);

    /**
     * The audio manager.
     */
    static AudioManager* mAudioManager;

    /**
     * The sound loop listeners.
     */
    static std::list<SoundStoppedListener*> mSoundStoppedListeners;

    /**
     * The properties of the audio device.
     */
    static int mFrequency;
    static Uint16 mFormat;
    static int mChannels;
    static int mChunkSize;

    /**
     * @brief Manage all audio aspects of the game.
     */
    AudioManager();

    /**
     * The music collection.
     */
    typedef std::map<std::string, Mix_Music*> MusicCollection;
    MusicCollection mMusicCollection;

    /**
     * The sound collection.
     */
    typedef std::map<std::string, Mix_Chunk*> SoundCollection;
    SoundCollection mSoundCollection;
};

#endif /* AUDIOMANAGER_HPP_ */
