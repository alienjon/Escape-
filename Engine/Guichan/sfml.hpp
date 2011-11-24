/*
 * sfml.hpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#ifndef SFML_HPP_
#define SFML_HPP_

#include "sfml/sfmlfont.hpp"
#include "sfml/sfmlgraphics.hpp"
#include "sfml/sfmlimage.hpp"
#include "sfml/sfmlimageloader.hpp"
#include "sfml/sfmlinput.hpp"

#include "platform.hpp"

extern "C"
{
    /**
     * Exists to be able to check for Guichan SDL with autotools.
     */
    extern void gcnSDL();
}

#endif /* SFML_HPP_ */
