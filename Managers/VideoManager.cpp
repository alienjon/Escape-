/*
 * VideoManager.cpp
 *
 *  Created on: Jul 2, 2009
 *      Author: alienjon
 */

#include "VideoManager.hpp"

#include <stdexcept>

#include "SDL/SDL_image.h"

#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::list;
using std::map;
using std::runtime_error;
using std::string;
VideoManager::VideoManager()
{
    // An image loader is needed for GUIchan draw methods.
    gcn::Image::setImageLoader(this);
}

VideoManager::~VideoManager()
{
	// Clear all the images.
	for(list<Surface*>::iterator it = mLoadedImages.begin(); it != mLoadedImages.end(); ++it)
	{
		delete *it;
	}
	mLoadedImages.clear();

	// Clear all the surfaces.
    for(map<string, SDL_Surface*>::iterator it = mLoadedSurfaces.begin(); it != mLoadedSurfaces.end(); ++it)
    {
        SDL_FreeSurface(it->second);
    }
    mLoadedSurfaces.clear();

    // Clear the image loader.
    gcn::Image::setImageLoader(0);
}

SDL_Surface* VideoManager::mConvertSurface(SDL_Surface* surface)
{
	// Make sure the surface exists.
	if(!surface)
	{
		throw runtime_error("ImageLoaderExt::mConvertSurface() -> Null surface provided.");
	}

	// NOTE: This is altered guichan code.
    int i;
    bool hasPink = false;
    bool hasAlpha = false;

    for (i = 0; i < surface->w * surface->h; ++i)
    {
        if (((unsigned int*)surface->pixels)[i] == SDL_MapRGB(surface->format,255,0,255))
        {
            hasPink = true;
            break;
        }
    }

    for (i = 0; i < surface->w * surface->h; ++i)
    {
        Uint8 r, g, b, a;

        SDL_GetRGBA(((unsigned int*)surface->pixels)[i], surface->format,
                    &r, &g, &b, &a);

        if (a != 255)
        {
            hasAlpha = true;
            break;
        }
    }

    SDL_Surface *tmp;

    if (hasAlpha)
    {
        tmp = SDL_DisplayFormatAlpha(surface);
        surface = 0;
    }
    else
    {
        tmp = SDL_DisplayFormat(surface);
        surface = 0;
    }

    if (hasPink)
    {
        SDL_SetColorKey(tmp, SDL_SRCCOLORKEY | SDL_RLEACCEL,
                        SDL_MapRGB(tmp->format,255,0,255));
    }
    if (hasAlpha)
    {
        SDL_SetAlpha(tmp, SDL_SRCALPHA | SDL_RLEACCEL, 255);
    }

	return tmp;
}

Surface* VideoManager::mCreateImage(const string& filename, const Rectangle& area, bool convert)
{
	// Create the image.
	Surface* image = new Surface(mGenerateSurface(filename, convert), area);

	// Store the image.
	mLoadedImages.push_back(image);

	// Return the created image.
	return image;
}

SDL_Surface* VideoManager::mFindSurface(const string& filename)
{
	// If the surface is already loaded, then create a new image with that surface.
	map<string, SDL_Surface*>::iterator pos = mLoadedSurfaces.find(filename);

	return (pos == mLoadedSurfaces.end()) ? 0 : pos->second;
}

SDL_Surface* VideoManager::mGenerateSurface(const string& filename, bool convert)
{
	// The new surface.
	SDL_Surface* surface = mFindSurface(filename);

	// If the image wasn't loaded, try loading it.
	if(!surface)
	{
		/*
		 * @todo I could use this code to simplify things, but - again - sticking with the
		 * guichan code seems to be the smarter choice because it does the right thing
		 * and allows for both an alpha value and color keying.  Of note is that RLE
		 * can be used with both SDL_SRCCOLORKEY and SDL_SRCALPHA but should ONLY BE
		 * used for surfaces which are not changed.  When I load surfaces from an image
		 * they are all (at least right now all) static images, in that alterations
		 * are not made to the physical image itself.  It is in these cases that RLE
		 * can greatly improve performance.  In any case, I'm keeping this information here
		 * only until I hear back from the Gentoo forums and determine if there is a
		 * better/faster way of loading/optimizing surfaces.
		 */
//		SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
//		if(!loadedSurface)
//		{
//			throw runtime_error("VideoManager::mGenerateSurface() -> '" + filename + "' unable to load.");
//		}
//		SDL_SetColorKey(loadedSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(loadedSurface->format, 255, 0, 255));
//		surface = SDL_DisplayFormat(loadedSurface);
//		SDL_FreeSurface(loadedSurface);
//		mLoadedSurfaces[filename] = surface;
		// Load the surface.
		SDL_Surface* loadedSurface = mLoadSurface(filename);

		// Convert the surface, if needed.
		if(convert)
		{
			surface = mConvertSurface(loadedSurface);
			SDL_FreeSurface(loadedSurface);
		}
		else
		{
			surface = loadedSurface;
		}

		// Store the surface after all the conversions have taken place.
		mLoadedSurfaces[filename] = surface;
	}

	// Return the surface.
	return surface;
}

SDL_Surface* VideoManager::mLoadSurface(const string& filename)
{
	// Load the surface.
	SDL_Surface* loadedSurface = loadSDLSurface(filename);

	// Error check.
	if(!loadedSurface)
	{
		throw runtime_error(string("ImageLoaderExt::mLoadSurface() -> Unable to load image '") + filename + string("': ") + string(SDL_GetError()));
	}

	// Convert to standard format.
	SDL_Surface* ret = convertToStandardFormat(loadedSurface);

	// Free the initial surface.
	SDL_FreeSurface(loadedSurface);

	// Error check.
	if(!ret)
	{
		throw runtime_error(string("ImageLoaderExt::mLoadSurface() -> Not enough memory to load image."));
	}

	return ret;
}

void VideoManager::create()
{
    if(!mVideoManager)
    {
        mVideoManager = new VideoManager;
    }
}

void VideoManager::displayVideoInfo()
{
    char videoDriverName[64];

    if(SDL_VideoDriverName(videoDriverName, 64))
    {
        Logger::log("Using video driver: " + string(videoDriverName));
    }
    else
    {
        Logger::log("Using video driver: unknown");
    }

    const SDL_VideoInfo* vi = SDL_GetVideoInfo();

    Logger::log("Possible to create hardware surfaces: " + boolToString(vi->hw_available));
    Logger::log("Window manager available: " + boolToString(vi->wm_available));
    Logger::log("Accelerated hardware to hardware blits: " + boolToString(vi->blit_hw));
    Logger::log("Accelerated hardware to hardware colorkey blits: " + boolToString(vi->blit_hw_CC));
    Logger::log("Accelerated hardware to hardware alpha blits: " + boolToString(vi->blit_hw_A));
    Logger::log("Accelerated software to hardware blits: " + boolToString(vi->blit_sw));
    Logger::log("Accelerated software to hardware colorkey blits: " + boolToString(vi->blit_sw_CC));
    Logger::log("Accelerated software to hardware alpha blits: " + boolToString(vi->blit_sw_A));
    Logger::log("Accelerated color fills: " + boolToString(vi->blit_fill));
    Logger::log("Available video memory: " + toString(vi->video_mem));
}

Surface* VideoManager::loadSurface(const string& filename, const Rectangle& area)
{
    if(mVideoManager && !filename.empty())
    {
    	return mVideoManager->mCreateImage(filename, area);
    }
    else
    {
        throw runtime_error(string("VideoManager::loadSurface() -> Video manager not created or empty file provided: ") + filename);
    }
}

gcn::Image* VideoManager::load(const string& filename, bool convert)
{
	// If the filename wasn't provided, then just return null.
	if(filename.empty())
	{
		return 0;
	}

	// Create an image.
	return mCreateImage(filename, NULL_RECTANGLE, convert);
}

void VideoManager::terminate()
{
    delete mVideoManager;
}

VideoManager* VideoManager::mVideoManager = 0;

const unsigned int SCREEN_HEIGHT = 600;
const unsigned int SCREEN_WIDTH = 800;

const char* FILE_GAME_ICON = "Images/icon.png";
