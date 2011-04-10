/*
 * TileData.cpp
 *
 *  Created on: Jul 13, 2010
 *      Author: the-saint
 */
#include "TileData.hpp"

using std::ostream;

TileData::TileData() :
	l(0),
	m(0),
	u1(0),
	u2(0),
	u3(0)
{}

void TileData::set(unsigned int _l, unsigned int _m, unsigned int _u1, unsigned int _u2, unsigned int _u3)
{
	l  = _l;
	m  = _m;
	u1 = _u1;
	u2 = _u2;
	u3 = _u3;
}

ostream& operator<<(ostream& os, const TileData& data)
{
	os << "[l:" << data.l << ", m:" << data.m << ", u1:" << data.u1 << ", u2:" << data.u2 << ", u3:" << data.u3 << ']';
	return os;
}
