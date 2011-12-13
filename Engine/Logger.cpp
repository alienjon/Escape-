/***************************************************************************
 *   Copyright (C) 2008 by Jonathan Rosen   *
 *   holy.smoking.floorboards.batman@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "Logger.hpp"

#include <iostream>

#include "../main.hpp"
#include "../Engine/Engine.hpp"

using std::cout;
using std::endl;
using std::ios;
using std::string;

// The log file.
const char* FILE_LOG = "error.log";

Logger::Logger()
{
	// Open the log file.
	m_logFile.open(FILE_LOG, ios::out | ios::trunc);

	// Check to make sure the log file was properly opened.
	if(m_logFile.is_open())
	{
		m_output(string("Logging to ") + FILE_LOG);
		m_output("[Logfile for " + string(GAME_NAME) + " v" + GAME_VERSION + "]");
		m_output("---------------");
	}
	else
		cout << "Error in creating " << FILE_LOG << ". Logging all output to the console." << endl;
}

Logger::~Logger()
{
	// Close the log file.
	m_logFile.close();
	cout << "Log file closed." << endl;
}

void Logger::mLog(const string& s)
{
    // Now display the message.
    mLogger.m_output(s);
}

void Logger::m_output(const string& s)
{
	// Output all logged information to the log file.
	if(m_logFile.is_open())
		m_logFile << s << endl;

	if(Engine::isDebug())
		cout << s << endl;
}

void Logger::error(const string& error, const string& function, const string& filename, unsigned int line)
{
	mLog("Error: " + filename + "::" + function + "(" + toString(line) + ") -> " + error);
}

void Logger::log(const string& message)
{
	mLog("Log: " + message);
}

Logger Logger::mLogger;
