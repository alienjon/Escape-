/*
 * MusicNode.hpp
 *
 *  Created on: Aug 11, 2010
 *      Author: the-saint
 */
#ifndef MUSICNODE_HPP_
#define MUSICNODE_HPP_

#include <string>

#include "../PlotInfo/PlotNode.hpp"

/**
 * @brief A node that plays a piece of music.  This node essentially only sets the music
 * to play upon activation and allows the user to indicate the number of times to loop the
 * song.  All audio is located in the 'Audio/' folder.
 */
class MusicNode : public PlotNode
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param musicFile The filename of the music to play.
	 * @param loops The number of times to loop.  If set to zero then it loops indefinitely until told otherwise.
	 * @param fadeIn The amount of time to fade in the music.
	 * @param fadeOut The amount of time to fade out the music.
	 */
	MusicNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& musicFile, int loops = 0, unsigned int fadeIn = 0, unsigned int fadeOut = 0);

	/**
	 * @brief The node was activated. (start playing music)
	 */
	virtual void activate();

	/**
	 * @brief The node was deactivated. (stop playing music)
	 */
	virtual void deactivate();

	private:
	/**
	 * The song's filename.
	 */
	std::string mMusicFile;

	/**
	 * The number of times to loop the song.
	 */
	int mLoops;

	/**
	 * The amount of time to fade-in/out the music.
	 */
	unsigned int mFadeIn,
				 mFadeOut;
};

#endif /* MUSICNODE_HPP_ */
