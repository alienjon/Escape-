/*
 * TriggerManager.hpp
 *
 *  Created on: Sep 1, 2009
 *      Author: alienjon
 */

#ifndef TRIGGERMANAGER_HPP_
#define TRIGGERMANAGER_HPP_

#include <list>
#include <string>

#include "../Game/EnvironmentData.hpp"
#include "../Game/ExtractionImplementer.hpp"
#include "../Engine/Renderer.hpp"
#include "../Triggers/Trigger.hpp"

class Level;

/*
 * @brief An object to manage triggers within a level.
 */
class TriggerManager : public ExtractionImplementer
{
    public:
    /**
     * @brief Construct a default trigger manager.
     */
    TriggerManager();
    virtual ~TriggerManager();

    /**
     * @brief Add a trigger.
     * @param trigger The trigger to add.
     */
    virtual void addTrigger(Trigger* trigger);

    /**
     * @brief Draw the triggers.
     * @param graphics The graphics object.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Extract the manager's data.
     * @return The manager's extracted data.
     */
    virtual std::string extract() const;

    /**
     * @brief Load the manager's data from the extracted string.
     * @param level The current level.
     * @param data The data to load into the manager.
     */
    virtual void load(Level* level, const std::string& data);

    /**
     * @brief Perform trigger logic.
     * @param eData The environment data.
     */
    virtual void logic(EnvironmentData& eData);

    /**
     * @brief Remove a trigger.
     * @param trigger The trigger to remove.
     */
    virtual void removeTrigger(Trigger* trigger);

    private:
    /**
     * Delete and clear any current triggers.
     */
    void mDeleteTriggers();

    /**
     * The running triggers.
     */
    std::list<Trigger*> mTriggers;
};

#endif /* TRIGGERMANAGER_HPP_ */
