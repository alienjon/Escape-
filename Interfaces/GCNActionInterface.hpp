/*
 * GCNActionInterface.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: alienjon
 */
#ifndef GCNACTIONINTERFACE_HPP_
#define GCNACTIONINTERFACE_HPP_

#include <list>
#include <string>

#include "../Engine/guichan.hpp"

class GCNActionInterface
{
	public:
    /**
     * @brief Add an action listener.
     * @param listener The listener.
     */
    inline void addActionListener(gcn::ActionListener* listener)
    {
    	mActionListeners.push_back(listener);
    }

    /**
     * @brief Remove an action listener.
     * @param listener The listener.
     */
    inline void removeActionListener(gcn::ActionListener* listener)
    {
    	mActionListeners.remove(listener);
    }

	protected:
    /**
     * @brief Distribute a non-widget action event.
     * @param str The action event string.
     */
    void mDistributeActionEvent(const std::string& str)
    {
    	for(std::list<gcn::ActionListener*>::iterator it = mActionListeners.begin(); it != mActionListeners.end(); ++it)
    		(*it)->action(gcn::ActionEvent(0, str));
    }

	private:
    // The listeners.
    std::list<gcn::ActionListener*> mActionListeners;
};

#endif /* GCNACTIONINTERFACE_HPP_ */
