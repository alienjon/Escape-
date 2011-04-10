/*
 * LetterListener.hpp
 *
 *  Created on: Aug 19, 2009
 *      Author: alienjon
 */

#ifndef LETTERLISTENER_HPP_
#define LETTERLISTENER_HPP_

#include <string>

class Letter;

class LetterListener
{
    public:
    /**
     * @brief A letter was found.
     * @param letter The letter found.
     */
    virtual void letterReceived(Letter* letter) = 0;

    /**
     * @brief A letter was removed.
     * @param letter The letter removed.
     */
    virtual void letterRemoved(Letter* letter) = 0;
};

#endif /* LETTERLISTENER_HPP_ */
