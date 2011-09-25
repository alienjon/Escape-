/*
 * Trigger.hpp
 *
 *  Created on: Aug 11, 2009
 *      Author: alienjon
 */

#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_

#include <string>

#include "../guichan.hpp"

#include "../Actions/Action.hpp"
#include "../Engine/Renderer.hpp"

class EnvironmentData;

enum TriggerType
{
    TRIGGERTYPE_LEVEL_NEXT,
    TRIGGERTYPE_LEVEL_PREVIOUS,
    TRIGGERTYPE_EXPLOSION,
    TRIGGERTYPE_NULL
};

/**
 * @brief Get the string value of the trigger type.
 * @param type The trigger type.
 * @return The string value of the trigger type.
 */
std::string getTriggerType(TriggerType type);

/**
 * @brief Get the trigger type based on the string.
 * @param str The string.
 * @return The determined trigger type.
 */
TriggerType getTriggerType(const std::string& str);

/**
 * @brief A trigger checks for the presence of a single condition and then performs some actions.
 *
 * Similar to an Action, a trigger has a logic function (Action has Action::activate()) that checks
 * to see when certain conditions are met and will then add some actions to a certain action implementer.
 * (The conditions and the actions are based on derived classes.
 */
class Trigger
{
    public:
    virtual ~Trigger();

    /**
     * @brief Add an action to the list.
     * @param action The action to add.
     */
    virtual void addAction(Action* action);

    /**
     * @brief Clear all actions.
     */
    virtual void clearActions();

    /**
     * @brief Draw the trigger, if necessary.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(Renderer& renderer) = 0;

    /**
     * @brief Get the type of trigger.
     * @return The type of trigger.
     */
    virtual TriggerType getType() const;

    /**
     * @brief Perform trigger logic.
     * @param eData The environment in which the trigger resides.
     */
    virtual void logic(EnvironmentData& data) = 0;

    /**
     * @brief A trigger logic function that returns the running state of the trigger.
     * @param eData The environment data.
     * @return True if the trigger has been tripped and the trigger has completed actions.
     */
    bool tripCheck(EnvironmentData& eData);

    protected:
    /**
     * @brief A trigger checks for certain conditions to be set and then runs a certain set of actions.
     */
    Trigger();

    /**
     * This is the type of trigger.
     */
    TriggerType mType;

    /**
     * True if the trigger has been tripped.
     */
    bool mTripped;

    private:
    /**
     * The actions to perform when tripped.
     */
    ActionList mActions;
};

#endif /* TRIGGER_HPP_ */
