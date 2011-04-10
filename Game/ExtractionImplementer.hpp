/*
 * ExtractionImplementer.hpp
 *
 *  Created on: Aug 31, 2009
 *      Author: alienjon
 */

#ifndef EXTRACTIONIMPLEMENTER_HPP_
#define EXTRACTIONIMPLEMENTER_HPP_

#include <string>

class ExtractionImplementer
{
    public:
    /**
     * @brief Extract this trigger as a data string.
     * @return The data string representation of this trigger.
     */
    virtual std::string extract() const = 0;
};

#endif /* EXTRACTIONIMPLEMENTER_HPP_ */
