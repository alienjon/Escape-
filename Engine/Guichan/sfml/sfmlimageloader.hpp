/*
 * SFMLImageLoader.hpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#ifndef SFMLIMAGELOADER_HPP_
#define SFMLIMAGELOADER_HPP_

#include <string>

#include "../imageloader.hpp"

namespace gcn
{
	class Image;

	/**
	 * @brief A manager for most loaded surfaces.
	 */
	class SFMLImageLoader : public ImageLoader
	{
		public:
		/**
		 * @brief Load an image for the GUI.
		 * @param filename The filename of the image.
		 * @param convertToDisplayFormat If true, convert the image to display format (not needed for SFML)
		 * @return The loaded image.
		 */
		virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true);
	};
}

#endif /* SFMLIMAGELOADER_HPP_ */
