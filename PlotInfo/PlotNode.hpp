/*
 * PlotNode.hpp
 *
 *  Created on: Jun 23, 2010
 *      Author: the-saint
 */
#ifndef PLOTNODE_HPP_
#define PLOTNODE_HPP_

#include <list>
#include <string>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../PlotInfo/PlotEvent.hpp"
#include "../Listeners/PlotListener.hpp"

/**
 * @brief Plots consist of devices.  Each device remains dormant but listening to the plot
 * until an activating keyword is passed.  When it is passed then the node activates and
 * will continue activating until it is performed.  Some nodes also listen for a deactivation
 * keyword which, when heard, will stop the node from activating and will consider it performed.
 * Once a node is performed, it is removed.
 *
 * The PlotNode is the base class for all plot devices.
 *
 * @note Plot nodes are strikingly similar to Actions, except that whereas Actions occur one at a time,
 * there can be many plot nodes occurring at once and plot nodes keep track of their own activation
 * and deactivation conditions (this is controlled externally for actions)
 */
class PlotNode : public CreatureMovedToPointListener, public EventInterface, public PlotListener
{
	public:
	/**
	 * This is the type for PlotNode keywords.
	 */
	typedef std::list<std::string> NodeKeywordSet;

	/**
	 * @brief Default constructor.
	 * @param This node's keyword.
	 * @param activation The activation keywords.
	 * @param deactivation The deactivation keywords.
	 */
	PlotNode(const std::string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation);
	virtual ~PlotNode();

	/**
	 * @brief Activate the node.
	 */
	virtual void activate();

	/**
	 * @brief Add a plot listener.
	 * @param listener The listener to add.
	 */
	void addPlotListener(PlotListener* listener);

	/**
	 * @brief Listen for when a creature has moved.
	 * @param creature The creature that moved.
	 */
	virtual void creatureMoved(Creature& creature);

	/**
	 * @brief Deactivate the node.
	 */
	virtual void deactivate();

	/**
	 * @brief Determines if the node is active or not.
	 * @return True if the node is activated.
	 */
	bool isActivated() const;

	/**
	 * @brief Perform logic.
	 * @return If the node has been performed by the end of the logic call, return true.
	 *
	 * @note DON'T need to check if the node is activated.  It is done before this method is called.
	 */
	virtual bool logic();

	/**
	 * @brief A plot event occurred.
	 * @param event The plot event.
	 */
	virtual void plotOccurance(const PlotEvent& event);

	/**
	 * @brief Remove a plot listener.
	 * @param listener The listener to remove.
	 */
	void removePlotListener(PlotListener* listener);

	/**
	 * @brief Run the node.
	 * @return True if the node has completed performing.
	 *
	 * @note This method will call the node-specific logic.
	 */
	bool run();

	protected:
	/**
	 * @brief Distribute a plot event to the listeners.
	 *
	 * @note This MUST be called by children of this class when appropriate (usually when performed, but potentially otherwise).
	 */
	void mDistributePlotEvent();

	/**
	 * The keywords.
	 */
	std::string mKeyword,
				mActivationKeyword,
				mDeactivationKeyword;

	/**
	 * The activated and performed state.
	 */
	bool mIsActivated,
		 mIsPerformed;

	private:
	/**
	 * The plot listeners.
	 */
	std::list<PlotListener*> mPlotListeners;

	/**
	 * The activation and deactivation conditionals.
	 */
	NodeKeywordSet mActivationConditionals;
	NodeKeywordSet mDeactivationConditionals;
};

// The plot devices.
extern const std::string PLOTDEVICE_EVENT_DEBUG;
extern const std::string PLOTDEVICE_EVENT_ENVIRONMENT;
extern const std::string PLOTDEVICE_EVENT_CONVERSATION;
extern const std::string PLOTDEVICE_EVENT_PAUSE;
extern const std::string PLOTDEVICE_EVENT_GAMEPAUSE;
extern const std::string PLOTDEVICE_EVENT_TASK;
extern const std::string PLOTDEVICE_EVENT_MESSAGE;
extern const std::string PLOTDEVICE_EVENT_GOTO;
extern const std::string PLOTDEVICE_EVENT_ADDENTITY;
extern const std::string PLOTDEVICE_EVENT_REMOVEENTITY;
extern const std::string PLOTDEVICE_EVENT_WALKTO;
extern const std::string PLOTDEVICE_EVENT_HOLDINPUT;
extern const std::string PLOTDEVICE_EVENT_MUSIC;
extern const std::string PLOTDEVICE_EVENT_SOUND;
extern const std::string PLOTDEVICE_EVENT_CREATURECONFIG;
extern const std::string PLOTDEVICE_EVENT_ENDGAME;

#endif /* PLOTNODE_HPP_ */
