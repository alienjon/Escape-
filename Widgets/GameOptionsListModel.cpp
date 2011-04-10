/*
 * GameOptionsListModel.cpp
 *
 *  Created on: Jun 29, 2010
 *      Author: the-saint
 */
#include "GameOptionsListModel.hpp"

#include <stdexcept>

using std::out_of_range;
using std::string;

void GameOptionsListModel::addOption(const string& option)
{
	mOptions.push_back(option);
}

string GameOptionsListModel::getElementAt(int i)
{
	try
	{
		return mOptions.at(i);
	}
	catch(out_of_range& e)
	{
		return "";
	}
}

int GameOptionsListModel::getNumberOfElements()
{
	return mOptions.size();
}
