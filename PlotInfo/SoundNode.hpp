/*
 * SoundNode.hpp
 *
 *  Created on: Aug 10, 2010
 *      Author: the-saint
 */
#ifndef SOUNDNODE_HPP_
#define SOUNDNODE_HPP_

#include <string>

#include "PlotNode.hpp"
#include "../Listeners/SoundStoppedListener.hpp"

/**
 * @brief A sound node plays an audio sound and deactivates after it has played.
 */
class SoundNode : public PlotNode, public SoundStoppedListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The node's keyword.
	 * @param activation The node's activation keywords.
	 * @param deactivation The deactivation keywords.
	 * @param soundfile The sound file to play.
	 * @param loops The number of times to repeat (0 plays once, 1 plays twice, etc...)
	 *
	 * @note The sound file is located in the 'Sounds/' directory.
	 */
	SoundNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const std::string& soundfile, int loops);
	virtual	~SoundNode();

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	/**
	 * @brief Deactivate the node.
	 */
	virtual void deactivate();

	/**
	 * @brief A sound has stopped.
	 * @param channel The channel of the stopped sound.
	 */
	virtual void soundStopped(int channel);

	private:
	/**
	 * The sound's filename.
	 */
	std::string mSoundFile;

	/**
	 * The number of times to loop the sound.
	 */
	int mLoops;

	/**
	 * The channel of the sound this node is listening for.
	 */
	int mChannel;
};

#endif /* SOUNDNODE_HPP_ */
