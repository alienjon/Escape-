/*
 * Trigger.cpp
 *
 *  Created on: Aug 11, 2009
 *      Author: alienjon
 */
#include "Trigger.hpp"

using std::string;

const string STRING_TRIGGERTYPE_LEVEL_NEXT = "TRIGGER_NEXTLEVEL";
const string STRING_TRIGGERTYPE_LEVEL_PREVIOUS = "TRIGGER_PREVIOUSLEVEL";
const string STRING_TRIGGERTYPE_EXPLOSION = "TRIGGER_EXPLOSION";
const string STRING_TRIGGERTYPE_NULL = "TRIGGER_NULL";

string getTriggerType(TriggerType type)
{
    switch(type)
    {
        case TRIGGERTYPE_LEVEL_NEXT:
        {
            return STRING_TRIGGERTYPE_LEVEL_NEXT;
        }
        case TRIGGERTYPE_LEVEL_PREVIOUS:
        {
            return STRING_TRIGGERTYPE_LEVEL_PREVIOUS;
        }
        case TRIGGERTYPE_EXPLOSION:
        {
            return STRING_TRIGGERTYPE_EXPLOSION;
        }
        default:
        {
            return STRING_TRIGGERTYPE_NULL;
        }
    }
}

TriggerType getTriggerType(const string& str)
{
    if(str == STRING_TRIGGERTYPE_LEVEL_NEXT)
    {
        return TRIGGERTYPE_LEVEL_NEXT;
    }
    else if(str == STRING_TRIGGERTYPE_LEVEL_PREVIOUS)
    {
        return TRIGGERTYPE_LEVEL_PREVIOUS;
    }
    else if(str == STRING_TRIGGERTYPE_EXPLOSION)
    {
        return TRIGGERTYPE_EXPLOSION;
    }
    else
    {
        return TRIGGERTYPE_NULL;
    }
}

Trigger::Trigger() : mType(TRIGGERTYPE_NULL),
                     mTripped(false)
{
}

Trigger::~Trigger()
{
    // Delete any remaining actions.
    clearActions();
}

void Trigger::addAction(Action* action)
{
    mActions.push_back(action);
}

void Trigger::clearActions()
{
    for(ActionList::iterator it = mActions.begin(); it != mActions.end(); ++it)
    {
        delete *it;
    }
    mActions.clear();
}

TriggerType Trigger::getType() const
{
    return mType;
}

bool Trigger::tripCheck(EnvironmentData& eData)
{
    // If the trigger has not yet been tripped, then call the trigger's logic.
    if(!mTripped)
    {
        logic(eData);
    }
    else
    {
        if(!mActions.empty())
        {
            Action* temp = *(mActions.begin());
            temp->activate(eData);

            // If that action is now performed, then remove it.
            if(temp->isPerformed())
            {
                mActions.pop_front();
                delete temp;
            }
        }
    }

    // Return the tripped state.
    return mTripped && mActions.empty();
}
