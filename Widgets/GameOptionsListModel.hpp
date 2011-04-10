/*
 * GameOptionsListModel.hpp
 *
 *  Created on: Jun 29, 2010
 *      Author: the-saint
 */

#ifndef GAMEOPTIONSLISTMODEL_HPP_
#define GAMEOPTIONSLISTMODEL_HPP_

#include <string>
#include <vector>

#include "../guichan.hpp"

/**
 * @brief The widget to select the various things the game screen options widget can do.
 */
class GameOptionsListModel : public gcn::ListModel
{
	public:
	/**
	 * @brief Add an option.
	 * @param option The option to add.
	 */
	virtual void addOption(const std::string& option);

	/**
	 * @brief Get the element at the provided position.
	 * @param i The element number.
	 * @return The name of the element.
	 */
	virtual std::string getElementAt(int i);

	/**
	 * @brief Get the total number of elements.
	 * @return the total number of elements.
	 */
	virtual int getNumberOfElements();

	private:
	/**
	 * This is a collection of the options.
	 */
	std::vector<std::string> mOptions;
};

#endif /* GAMEOPTIONSLISTBOX_HPP_ */
