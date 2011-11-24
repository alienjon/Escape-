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

using std::cout;
using std::endl;
using std::ios;
using std::string;

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
	{
		cout << "Error in creating " << FILE_LOG << ". Logging all output to the console." << endl;
	}
}

Logger::~Logger()
{
	// Close the log file.
	m_logFile.close();
	cout << "Log file closed." << endl;
}

void Logger::mLog(const string& s)
{
    // Check to make sure the logger is created.
    if(mLogger == 0)
    {
        mLogger = new Logger();
    }

    // Now display the message.
    mLogger->m_output(s);
}

void Logger::m_output(const string& s)
{
	// Output all logged information to the log file.
	if(m_logFile.is_open())
	{
		m_logFile << s << endl;
	}

    cout << s << endl;
}

void Logger::terminate()
{
    delete mLogger;
}

void Logger::error(const gcn::Exception& e)
{
	mLog("Guichan error: " + e.getFilename() + "::" + e.getFunction() + "(" + toString(e.getLine()) + ")->" +  e.getMessage());
}

void Logger::error(const std::domain_error& e)
{
	mLog("Domain error: " + string(e.what()));
}

void Logger::error(const std::invalid_argument& e)
{
	mLog("Invalid argument error: " + string(e.what()));
}

void Logger::error(const std::length_error& e)
{
	mLog("Length error: " + string(e.what()));
}

void Logger::error(const std::out_of_range& e)
{
	mLog("Out of range error: " + string(e.what()));
}

void Logger::error(const std::logic_error& e)
{
	mLog("Logic error: " + string(e.what()));
}

void Logger::error(const std::range_error e)
{
	mLog("Range error: " + string(e.what()));
}

void Logger::error(const std::overflow_error& e)
{
	mLog("Overflow error: " + string(e.what()));
}

void Logger::error(const std::underflow_error& e)
{
	mLog("Underflow error: " + string(e.what()));
}

void Logger::error(const std::runtime_error& e)
{
	mLog("Runtime error: " + string(e.what()));
}

void Logger::error(const std::exception& e)
{
	mLog("General STD error: " + string(e.what()));
}

void Logger::error(const string& error)
{
	mLog("Error: " + error);
}

void Logger::log(const string& message)
{
	mLog("Log: " + message);
}

void Logger::warn(const string& warning)
{
	mLog("Warning: " + warning);
}

Logger* Logger::mLogger = 0;

const char* Logger::FILE_LOG = "error.log";
