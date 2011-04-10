/*
 * PlotEvent.cpp
 *
 *  Created on: Jun 23, 2010
 *      Author: the-saint
 */

#include "PlotEvent.hpp"

using std::string;

PlotEvent::PlotEvent(const string& keyword, const string& data) :
	mKeyword(keyword),
	mData(data)
{
}

const string& PlotEvent::getData() const
{
	return mData;
}

const string& PlotEvent::getKeyword() const
{
	return mKeyword;
}
