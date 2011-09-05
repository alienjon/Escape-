/*
 * LoadGameListModel.hpp
 *
 *  Created on: Jul 7, 2009
 *      Author: alienjon
 */

#ifndef LOADGAMELISTMODEL_HPP_
#define LOADGAMELISTMODEL_HPP_

#include <fstream>
#include <string>
#include <vector>

#include "../../../guichan.hpp"

/**
 * @brief A list model for the load game menu widget.
 */
class LoadGameListModel : public gcn::ListModel
{
    public:
    /**
     * @brief A list model for loading a game.
     */
    LoadGameListModel();

    /**
     * @brief Get the element at the specified indicator.
     * @param i The position of the element to return.
     * @return The name of the element at the indicator.
     */
    virtual std::string getElementAt(int i);

    /**
     * @brief Return the number of elements.
     * @return The number of elements.
     */
    virtual int getNumberOfElements();

    private:
    /**
     * The list of loaded games.
     */
    std::vector<std::string> mGameList;
};

#endif /* LOADGAMELISTMODEL_HPP_ */
