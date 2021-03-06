/*
 * DebugAction.hpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */
#ifndef DEBUGACTION_HPP_
#define DEBUGACTION_HPP_

#include <string>

#include "../Actions/Action.hpp"

/**
 * @brief An action to display a console message for debugging purposes.
 */
class DebugAction : public Action
{
    public:
    /**
     * @brief Outputs a console message.
     */
    DebugAction(const std::string& message);

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    private:
    /**
     * The message.
     */
    std::string mMessage;
};

#endif /* DEBUGACTION_HPP_ */
