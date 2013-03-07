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
#include <SFML/Audio.hpp>
#include <string>

/**
 * @brief A class that manages both music and sound effects.
 */
class AudioManager
{
    public:
    /**
     * @brief Create the audio manager.
     */
    static void create();

    /**
     * @brief Get the music level.
     * @return The music level.
     */
    static unsigned int getMusicLevel();

    /**
     * @brief Get the sound level.
     * @return The sound level.
     */
    static unsigned int getSoundLevel();

    /**
     * @brief Get a sound to play.
     * @param filename The filename of the sound.
     */
    static void playSound(const std::string& filename);

    /**
     * @brief Set the global music level.
     * @param level The music level.
     * @note The level will be clipped between [0,100]
     */
    static void setMusicLevel(unsigned int level);

    /**
     * @brief Set the global sound level.
     * @param level The sound level.
     * @note The level will be clipped between [0,100]
     */
    static void setSoundLevel(unsigned int level);

    /**
     * @brief Delete the manager.
     */
    static void terminate();

    protected:
    // The audio manager.
    static AudioManager* mAudioManager;

    // The volume levels.
    static unsigned int mMusicLevel, mSoundLevel;

    /**
     * @brief Manage all audio aspects of the game.
     */
    AudioManager();

    /**
     * @brief Get the sound buffer based on its filename.
     * @param filename The filename of the sound buffer.
     * @return The sound buffer.
     */
    sf::SoundBuffer& mGetSoundBuffer(const std::string& filename);

    // The audio collections.
    std::map<std::string, sf::SoundBuffer> mSounds;

    // This is the list of playing sounds.  When playSound() is called, all stopped sounds are removed.
    std::list<sf::Sound> mPlayingSounds;
};

#endif /* AUDIOMANAGER_HPP_ */
