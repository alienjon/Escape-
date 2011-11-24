/*
 * VideoManager.hpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#ifndef VIDEOMANAGER_HPP_
#define VIDEOMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

/*
 * @brief Implementation of SFMLImageLoader
 */
class VideoManager : public gcn::SFMLImageLoader
{
	public:
	virtual ~VideoManager();

	/**
	 * @brief Create the video manager.
	 */
	static void create();

	/**
	 * @brief Get a requested sprite.
	 * @param filename The filename of the sprite.
	 * @return The requested sprite.
	 */
	static const sf::Texture& getTexture(const std::string& filename);

	/**
	 * @brief Delete the video manager.
	 */
	static void terminate();

	/**
	 * @brief Load an image for the GUI.
	 * @param filename The filename of the image.
	 * @param convertToDisplayFormat If true, convert the image to display format (not needed for SFML)
	 * @return The loaded image.
	 * @note Overloaded to store the images.
	 */
	virtual gcn::Image* load(const std::string& filename, bool convertToDisplayFormat = true);

	protected:
	/**
	 * The video manager.
	 */
	static VideoManager* mVideoManager;

	/**
	 * @brief The video manager details all non-rendering video-specific aspects of the games graphics.
	 */
	VideoManager();

	private:
	// The collection of loaded surfaces.
	std::map<std::string, sf::Texture> mTextures;
	std::map<std::string, gcn::Image*> mGCNImages;
};

#endif /* VIDEOMANAGER_HPP_ */
