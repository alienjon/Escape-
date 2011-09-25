/**
 * main.cpp - Start point for the program.
 * @author alienjon
 * @email holy.smoking.floorboards.batman@gmail.com
 */
#include <limits>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include <SDL/SDL_image.h>

#include "Game/Direction.hpp"
#include "Game/Event.hpp"
#include "Game/Game.hpp"
#include "Engine/Logger.hpp"
#include "main.hpp"

using std::clog;
using std::cout;
using std::endl;
using std::exception;
using std::list;
using std::string;

const char CHAR_DELIMITER			= ':';
const char CHAR_DELIMITER_ALTERNATE = '~';

string boolToString(bool state)
{
	if(state)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

SDL_Surface* loadSurface(const string& filename)
{
	// Load the image to an SDL_Surface.
	SDL_Surface* newSurface = IMG_Load(filename.c_str());

	// If the image isn't loaded, error out.
	if(!newSurface)
	{
	    Logger::log("Load_Surface() -> File Not Found: " + filename);
		return 0;
	}

	// Set the transparent color to transparent pink.
	SDL_SetColorKey(newSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(newSurface->format, 255, 0, 255));

	// Optimize the image, ignoring the alpha channel (configuring the alpha channel won't work with alpha blending)
	SDL_Surface* returnSurface = SDL_DisplayFormatAlpha(newSurface);

	// Free the old surface.
	SDL_FreeSurface(newSurface);

	return returnSurface;
}

string replace(const string& str, const char ch, const char re)
{
    // The return string.
    string ret(str);

    // Replace the requested characters.
    for(string::size_type pos = 0; pos != ret.size(); ++pos)
    {
        if(ret[pos] == ch)
        {
            ret[pos] = re;
        }
    }

    return ret;
}

bool isColon(char c)
{
    return c == ':';
}

bool isSpace(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

string extractDataLine(const string& data, string::size_type& pos, const char del)
{
    string::size_type end = data.find_first_of(del, pos);
    string ret = data.substr(pos, end - pos);
    pos = (end == string::npos) ? data.size() : end + 1;
    return ret;
}

list<string> extractDataAsCollection(const string& data, const string& del)
{
        list<string> ret;

        string::size_type beg = 0,
                          end = data.find_first_of(del);
        ret.push_back(data.substr(beg, end - beg));
        while(end != string::npos)
        {
                beg = end + 1;
                end = data.find_first_of(del, beg);
                ret.push_back(data.substr(beg - 1, end - beg + 1));
        }

        return ret;
}

string extractFilename(const string& filename)
{
    string::size_type beg = filename.find_last_of('/') + 1;
    if(beg >= filename.size())
    {
            return "";
    }
    return filename.substr(beg, filename.find_last_of('.') - beg);

}

string formatStringToFit(string str, gcn::Font* font, const int width)
{
	// Double check the provided font.
	if(!font)
	{
		throw std::runtime_error("formatStringToFit() -> No font provided.");
	}

	// If no width was provided, just return.
	if(!width)
	{
		return str;
	}

	// Convert all string-based new lines to actual newlines (string("\\n") to '\n').
	string::size_type pos = str.find("\\n");
	while(pos != string::npos)
	{
		str.replace(pos, 2, 1, '\n');
		pos = str.find("\\n", pos);
	}

	// Calculate the string.
	string::size_type beg = 0, end = 0;
	for(; end != str.size() && beg != string::npos; ++end)
	{
		// If the next character is a newline, then reset the beginning space.
		if(str[end] == '\n')
		{
			beg = end;
		}
		// We've reached the next position to fit the size.
		else if(font->getWidth(str.substr(beg, end - beg)) >= width)
		{
			// Find the last space in this segment.
			//	If the last space is the last character in the segment, then go one word previous
			//	unless this is the first character.
			string::size_type last_space = str.find_last_of(' ', end);
			if(last_space == end && beg != end)
			{
				last_space = str.find_last_of(' ', end - 1);
			}

			// So long as the replacing character position is not the end of the string,
			//	then replace the space with a newline.
			if(last_space != string::npos)
			{
				str[last_space] = '\n';
			}

			// Set the beginning of the next segment as the end of this segment.
			beg = last_space;
		}
	}

	// Check to make sure the last character does not go over the desired width.
	if(beg != string::npos && font->getWidth(str.substr(beg, end - beg)) >= width)
	{
		string::size_type last_space = str.find_last_of(' ', end);
		if(last_space == end && beg != end)
		{
			last_space = str.find_last_of(' ', end - 1);
		}

		// So long as the replacing character position is not the end of the string,
		//	then replace the space with a newline.
		if(last_space != string::npos)
		{
			str[last_space] = '\n';
		}
	}

	// Return the string.
	return str;
}

bool isVectorInTriangle(const Vector& a, const Vector& b, const Vector& c, const Vector& p)
{
    /* Cred goes to blackspawn for the math behind this */
    // Compute vectors.
    Vector v0 = c - a,
          v1 = b - a,
          v2 = p - a;

    // Compute dot products.
    double d00 = v0.dotProduct(v0),
           d01 = v0.dotProduct(v1),
           d02 = v0.dotProduct(v2),
           d11 = v1.dotProduct(v1),
           d12 = v1.dotProduct(v2);

    // Compute barycentric coordinates (whatever that is).
    double invertedDenominator = 1 / ((d00 * d11) - (d01 * d01));
    double u = ((d11 * d02) - (d01 * d12)) * invertedDenominator,
           v = ((d00 * d12) - (d01 * d02)) * invertedDenominator;

    // The vector is within the triangle's boundaries if u and v are, independently, greater than 0 and, combined, less than 1.
    return (u > 0) && (v > 0) && (u + v < 1);
}

void displayVersion()
{
    clog << GAME_NAME << ": v." << GAME_VERSION << endl;
}

void displayUsage()
{
    clog << "Usage: Escape [PARAMETER]\n"
         << "\t-v, --version    Display version information.\n"
         << "\t-h, --help       Display this usage information.\n"
         << "\t-d, --debug      Run the game with debugging warnings (errors are shown regardless\n"
         << endl;
}

int main(int args, const char** pArgs)
{
    // Parse the arguments.
	for(int c = 1; c != args; ++c)
	{
		string arg(pArgs[c]);
		if(arg == "-v" || arg == "--version")
		{
			displayVersion();
			return 0;
		}
		else if(arg == "-h" || arg == "--help")
		{
			displayUsage();
			return 0;
		}
		else if(arg == "-d" || arg == "--debug")
		{
			Game::setDebug(true);
		}
	}

	// If the game is still running by now then start it up.
    try
    {
		// Create the game object.
		Game game;

		// Run the game.
		game.run();
    }
    catch(gcn::Exception& e)
    {
    	Logger::error(e);
        return 1;
    }
    catch(exception& e)
    {
        Logger::error(e);
        return 1;
    }
    catch(...)
    {
    	Logger::error("main.cpp::main() -> Unknown error running program.");
        return 1;
    }

    // Terminate the logger.
    Logger::terminate();

	// Exit.
	return 0;
}
