/**
 * main.cpp - Start point for the game.
 * @author alienjon
 * @email holy.smoking.floorboards.batman@gmail.com
 */
#include "main.hpp"

#include <iostream>
#include <stdexcept>

#include "Game/Game.hpp"
#include "Engine/Logger.hpp"

using std::clog;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::tolower;

string toLower(const string& str)
{
	string ret;
	for(string::const_iterator it = str.begin(); it != str.end(); it++)
		ret += tolower(*it);
	return ret;
}

string extractDataLine(const string& data, string::size_type& pos, const char del)
{
    string::size_type end = data.find_first_of(del, pos);
    string ret = data.substr(pos, end - pos);
    pos = (end == string::npos) ? data.size() : end + 1;
    return ret;
}

string convertToTimeFormat(const string& time)
{
    if(time.size() > 1)
        return time.substr(0, 2);
    else if(!time.empty())
        return "0" + time.substr(0, 1);
    else
        return "00";
}

string convertToTime(unsigned time)
{
    // Convert the time, damnit!
    string milliseconds = toString(time);
    if(time >= 1000)
    {
        milliseconds = milliseconds.substr(milliseconds.size() - 3);
    }
    unsigned int seconds = time / 1000;
    int seconds_formatted = (seconds < 60) ? seconds : seconds % 60;
    unsigned int minutes = seconds / 60;
    return convertToTimeFormat(toString(minutes)) + ":" + convertToTimeFormat(toString(seconds_formatted)) + ":" + convertToTimeFormat(milliseconds);
}

int main(int args, const char** pArgs)
{
    // Parse the arguments.
	for(int c = 1; c != args; ++c)
	{
		string arg(pArgs[c]);
		if(arg == "-v" || arg == "--version")
		{
			clog << GAME_NAME << ": v." << GAME_VERSION << endl;
			return 0;
		}
		else if(arg == "-h" || arg == "--help")
		{
		    clog << "Usage: Escape [PARAMETER]\n"
		         << "\t-v, --version    Display version information.\n"
		         << "\t-h, --help       Display this usage information.\n"
		         << "\t-d, --debug      Run the game with debugging settings.\n"
		         << "\n"
		         << "In-Game Options\n"
		         << "\tF1		Toggle debugging output.\n"
		         << "\tF2		Display game engine settings.\n"
		         << "\tCTRL+c		Force quit the game (debug enabled only).\n"
		         << "\tCTRL+p		Take a screenshot (saved in main game directory).\n"
		         << "\tALT+ENTER	Toggle fullscreen.\n"
		         << endl;
			return 0;
		}
		else if(arg == "-d" || arg == "--debug")
			Engine::setDebug(true);
	}

    try
    {
		// Create the game object.
		Game game;

		// Run the game.
		game.run();
    }
    catch(CEGUI::Exception& e)
    {
    	ERROR(string("(CEGUI) ") + e.getMessage().c_str());
		return 1;
    }
    catch(exception& e)
    {
        ERROR(string("(std) ") + e.what());
        return 1;
    }
    catch(...)
    {
    	ERROR("main.cpp::main() -> Unknown error running program.");
        return 1;
    }

	// Exit.
	return 0;
}

const unsigned int DEFAULT_SCREEN_HEIGHT = 600;
const unsigned int DEFAULT_SCREEN_WIDTH = 800;
const char* GAME_NAME = "Mazin' it Up";
const char* GAME_VERSION = "0.0";
const char DELIMITER = ':';
