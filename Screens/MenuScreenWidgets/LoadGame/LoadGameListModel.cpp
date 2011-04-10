/*
 * LoadGameListModel.cpp
 *
 *  Created on: Jul 7, 2009
 *      Author: alienjon
 */
#include "LoadGameListModel.hpp"

// @todo Implement boost filesystem libraries to read the filesystem and load games.
//#include "boost/filesystem.hpp"

//using namespace boost::filesystem;
using namespace std;

LoadGameListModel::LoadGameListModel()
{
}

string LoadGameListModel::getElementAt(int i)
{
    return mGameList.at(i);
}

int LoadGameListModel::getNumberOfElements()
{
    return mGameList.size();
}
