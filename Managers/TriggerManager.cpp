/*
 * TriggerManager.cpp
 *
 *  Created on: Sep 1, 2009
 *      Author: alienjon
 */

#include "TriggerManager.hpp"

#include "../Math/Base64Functions.hpp"
#include "../Triggers/ExplodingTrigger.hpp"
#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../Triggers/LoadLevelTrigger.hpp"

using std::list;
using std::string;

TriggerManager::TriggerManager()
{
}

TriggerManager::~TriggerManager()
{
    mDeleteTriggers();
}

void TriggerManager::mDeleteTriggers()
{
    // Delete all the triggers.
    for(list<Trigger*>::iterator it = mTriggers.begin(); it != mTriggers.end(); ++it)
    {
        delete *it;
    }
    mTriggers.clear();
}

void TriggerManager::addTrigger(Trigger* trigger)
{
    mTriggers.push_back(trigger);
}

void TriggerManager::draw(Renderer& renderer)
{
    for(list<Trigger*>::iterator it = mTriggers.begin(); it != mTriggers.end(); ++it)
    {
        (*it)->draw(renderer);
    }
}

string TriggerManager::extract() const
{
    // If there aren't any triggers, just exit.
    if(mTriggers.empty())
    {
        return "";
    }

    // The return string.
    string ret;
// @todo implement?
//    // Add the first trigger (so that the string doesn't end with a delimiter.
//    list<Trigger*>::const_iterator it = mTriggers.begin();
//    ret += getTriggerType((*it)->getType()) + CHAR_DELIMITER + encodeBase64((*it)->extract());
//    ++it;
//
//    // Add all of the triggers.
//    for(; it != mTriggers.end(); ++it)
//    {
//        ret += CHAR_DELIMITER + getTriggerType((*it)->getType()) + CHAR_DELIMITER + encodeBase64((*it)->extract());
//    }

    // Return the string.
    return ret;
}

void TriggerManager::load(Level* level, const string& data)
{
    // Clear any current data.
    mDeleteTriggers();

//    // While we haven't reached the end of the data string, determine the type of trigger and load the trigger.
//    string::size_type pos = 0;
//    while(pos != data.size())
//    {@todo implement loading levels
//
//        switch(getTriggerType(extractDataLine(data, pos, CHAR_DELIMITER)))
//        {
//            case TRIGGERTYPE_LEVEL_NEXT:
//            {
//                mTriggers.push_back(new LoadLevelTrigger(level, decodeBase64(extractDataLine(data, pos, CHAR_DELIMITER))));
//                break;
//            }
//            case TRIGGERTYPE_LEVEL_PREVIOUS:
//            {
//                mTriggers.push_back(new LoadLevelTrigger(level, decodeBase64(extractDataLine(data, pos, CHAR_DELIMITER))));
//                break;
//            }
//            case TRIGGERTYPE_EXPLOSION:
//            {
//                mTriggers.push_back(new ExplodingTrigger(decodeBase64(extractDataLine(data, pos, CHAR_DELIMITER))));
//                break;
//            }
//            default:
//            {
//                // Bad trigger type.  Need to clear out the data in the next section.
//                extractDataLine(data, pos, CHAR_DELIMITER);
//                Logger::log("TriggerManager::load() -> Invalid trigger type detected. Skipping...");
//            }
//        }
//    }
}

void TriggerManager::logic(EnvironmentData& eData)
{
    // Perform trigger logic.
    list<Trigger*> tripped;
    for(list<Trigger*>::iterator it = mTriggers.begin(); it != mTriggers.end(); ++it)
    {
        if((*it)->tripCheck(eData))
        {
            tripped.push_back(*it);
        }
    }

    // Remove and clear completed triggers.
    for(list<Trigger*>::iterator it = tripped.begin(); it != tripped.end(); ++it)
    {
        mTriggers.remove(*it);
        delete *it;
    }
    tripped.clear();
}

void TriggerManager::removeTrigger(Trigger* trigger)
{
    mTriggers.remove(trigger);
}
