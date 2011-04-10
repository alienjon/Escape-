/*
 * PlotManager.hpp
 *
 *  Created on: Jun 27, 2010
 *      Author: the-saint
 */

#ifndef PLOTMANAGER_HPP_
#define PLOTMANAGER_HPP_

#include <list>
#include <string>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Interfaces/EnvironmentInterface.hpp"
#include "../Game/Event.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Interfaces/GameInterfaceInterface.hpp"
#include "../PlotInfo/PlotEvent.hpp"
#include "../Listeners/PlotListener.hpp"
#include "../PlotInfo/PlotNode.hpp"

/**
 * @brief The plot manager is an external object to deal with plot objects.
 */
class PlotManager : public EnvironmentInterface, public EventInterface, public EventListener, public GameInterfaceInterface, public PlotListener
{
	friend class ConversationNode;
	friend class EnvironmentNode;
	friend class GoToNode;
	friend class MessageNode;
	friend class TaskNode;

	public:
	/**
	 * @brief Default constructor.
	 */
	PlotManager();
	virtual ~PlotManager();

	/**
	 * @brief Add a new plot node.
	 * @param data The node data.
	 */
	void addNode(const std::string& data);

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

	/**
	 * @brief Load the plot information.
	 */
	void load();

	/**
	 * @brief Perform logic.
	 */
	void logic();

	/**
	 * @brief A plot device occurred.
	 * @param event The plot event.
	 */
	void plotOccurance(const PlotEvent& event);

	private:
    /**
     * The plot information.
     */
    std::list<PlotNode*> mPlotNodes;
};

#endif /* PLOTMANAGER_HPP_ */
