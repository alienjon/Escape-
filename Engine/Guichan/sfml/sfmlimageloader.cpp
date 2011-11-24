/*
 * VideoManager.cpp
 *
 *  Created on: Jul 2, 2009
 *      Author: alienjon
 */
#include "sfmlimageloader.hpp"

#include "../exception.hpp"
#include "../image.hpp"
#include "sfmlimage.hpp"

namespace gcn
{
	Image* SFMLImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
	{
		return new SFMLImage(filename);
	}
}
