/*
 * VideoManager.hpp
 *
 *  Created on: Jul 2, 2009
 *      Author: alienjon
 */

#ifndef VIDEOMANAGER_HPP_
#define VIDEOMANAGER_HPP_

#include <list>
#include <map>
#include <string>

#include "SDL/SDL.h"

#include "../guichan.hpp"

#include "../Math/Rectangle.hpp"
#include "../Engine/Surface.hpp"

/**
 * @brief A manager for most loaded surfaces.
 *
 * The video manager manages, essentially, all loaded surfaces except some that need to
 * be managed by other objects (such as ImageFonts and blocks from meta surfaces)
 */
class VideoManager : public gcn::SDLImageLoader
{
    public:
    virtual ~VideoManager();

    /**
     * @brief Create the video manager.
     */
    static void create();

    /**
     * @brief Log the available video information.
     */
    static void displayVideoInfo();

    /**
     * @brief Loads a surface, but keeps it in Surface format.
     * @param filename The filename of the image to load.
     * @param area The area of the SDL_Surface* to display.
     * @return The surface.
     */
    static Surface* loadSurface(const std::string& filename, const Rectangle& area = NULL_RECTANGLE);

    /**
     * @brief Load an image from the filename.
     * @param filename The filename of the image to load.
     * @param convert Convert the image to display format.
     * @return The loaded image.
     *
     * @throws std::exception In the event that a problem presents during image load.
     *
     * Note, each imagefile is loaded once and stored with its associated string.  Each call to load(), however
     * creates a new gcn::Image (technically, a Surface).
     */
    virtual gcn::Image* load(const std::string& filename, bool convert = true);

    /**
     * @brief Delete the video manager.
     */
    static void terminate();

    protected:
    /**
     * The video manager.
     */
    static VideoManager* mVideoManager;

    /**
     * @brief The video manager details all non-rendering video-specific aspects of the games graphics.
     */
    VideoManager();

	/**
	 * @brief Convert the SDL surface to standard format.
	 * @param surface The surface to convert.
	 */
	SDL_Surface* mConvertSurface(SDL_Surface* surface);

	/**
	 * @brief Convert's the SDL_Surface to the display format and create a new image from it.
	 * @param filename The name of the file which the created image's surface was loaded.
	 * @param area The area of the SDL_Surface to draw.
	 * @param convert True if the image should be converted.
	 * @return The created/converted image.
	 */
	Surface* mCreateImage(const std::string& filename, const Rectangle& area, bool convert = true);

	/**
	 * @brief Finds a surface.
	 * @param filename The name of the surface.
	 * @return The surface, or null if not found.
	 */
	SDL_Surface* mFindSurface(const std::string& filename);

	/**
	 * @brief Load and convert an SDL_Surface.
	 * @param filename The filename of the surface.
	 * @param convert If true, convert to the display format.
	 */
	SDL_Surface* mGenerateSurface(const std::string& filename, bool convert = true);

	/**
	 * @brief Load the surface.
	 * @param filename The filename.
	 * @return The loaded surface.
	 * @note Needs to be freed later.
	 */
	SDL_Surface* mLoadSurface(const std::string& filename);

    private:
    /**
     * The collection of loaded surfaces.
     */
    std::map<std::string, SDL_Surface*> mLoadedSurfaces;

    /**
     * The created images.
     */
    std::list<Surface*> mLoadedImages;
};

// The screen dimension.
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

//The game icon.
extern const char* FILE_GAME_ICON;

#endif /* VIDEOMANAGER_HPP_ */
