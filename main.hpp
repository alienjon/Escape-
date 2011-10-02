/*
 * main.hpp
 *
 *  Created on: Mar 27, 2009
 *      Author: alienjon
 */
#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <algorithm>
#include <list>
#include <sstream>
#include <string>

#include "SDL/SDL.h"

#include "Game/Direction.hpp"
#include "guichan.hpp"
#include "Math/Vector.hpp"

// The delimiters.
extern const char CHAR_DELIMITER;
extern const char CHAR_DELIMITER_ALTERNATE;

/**
 * @brief Convert an object to a character string.
 * @param n The object to convert.
 * @return The string value of the object.
 */
template <class T>
std::string toString(const T& n)
{
    std::ostringstream outStream;
    outStream << n;

    return outStream.str();
}

/**
 * @brief Convert the provided object to an integer value.
 * @param s The object to convert.
 * @return The integer version of the parameter.
 */
template <class T>
int toInt(const T& s)
{
    std::stringstream str;
    str << s;
    int i;
    str >> i;
    return i;
}

/**
 * @brief Checks that 'low' is lower than 'high' and switches the two if necessary.
 * @param low The 'should be' lower value.
 * @param hight The 'should be' higher value.
 */
template <class T>
void checkFlip(T& low, T& high)
{
    if(low > high)
    {
        T temp = low;
        low = high;
        high = temp;
    }
}

/**
 * @brief Convert a bool value to a string.
 * @param state The bool value to convert.
 * @return The string value of the provided bool.
 */
std::string boolToString(bool state);

/**
 * @brief Loads an image as a surface.
 * @param filename Name of file to load.
 * @return A surface with the loaded image.
 */
SDL_Surface* loadSurface(const std::string& filename);

/**
 * @brief Returns a random integer between the low and high values.
 * @param low The lowest value inclusive to the random number.
 * @param high The highest value inclusive to the random number.
 * @return A random number within range.
 * @note If the low is equal to high, that number is returned.
 * @note If low is greater than high, then the values are switched and a random integer between the two are returned.
 */
template <class T>
T random(T low, T high)
{
    if(low == high)
    {
        return low;
    }

    // Check to make sure the lower value is not higher than the high value.
    checkFlip(low, high);

    return rand() % (high - low + 1) + low;
}

/**
 * @brief Replace certain characters in a string.
 * @param str The string to read.
 * @param ch The character to look for.
 * @param re The character to replace with.
 * @return A copy of the string to return.
 */
std::string replace(const std::string& str, const char ch, const char re);

/**
 * @brief Predicate to test if a character is equal to a space.
 * @param c The character to check.
 * @return True if the character provided is a space.
 */
bool isSpace(char c);

/**
 * @brief Predicate to test if a character is NOT a space.
 * @param c The character to check.
 * @return True if the character is not a space.
 */
bool not_space(char c);

/**
 * @brief Predicate to test if a character is equal to a colon.
 * @param c The character to check.
 * @return True if the character provided is a colon.
 */
bool isColon(char c);

/**
 * @brief Split the provided string by the provided delimiter.
 * @param s The string to split.
 * @param os The output iterator to use to add strings.
 * @param pred The prdicate to test for a delimiter.
 * @return A vector that has split up the entire string by its delimiter.
 */
template <class Out>
void split(const std::string& s, Out os, bool pred(char) = isSpace)
{
    typedef std::string::const_iterator iter;

    iter i = s.begin();
    while(i != s.end())
    {
        // ignore leading blanks
        i = find_if(i, s.end(), not_space);

        // find end of next word
        iter j = find_if(i + 1, s.end(), pred); // i + 1 so that find_if won't return 'i' if it is currently equal to the predicate

        if(i != s.end())
        {
            *os++ = std::string(i, j++); // After creating the string from positions i to j we want to skip over the predicate (hence j++)
        }

        // Set i to j.
        i = j;
    }
}

/**
 * @brief Extract certain data from a provided string.
 * @param data The base string data to read from.
 * @param pos The initial position to start looking.
 * @param del The delimiting character to stop looking at.
 * @return A string starting from 'pos' and ending the character before the delimiter.
 * @note This function changes 'pos' so that when it returns it will point to one position past the last found delimiter.
 */
std::string extractDataLine(const std::string& data, std::string::size_type& pos, const char del = ':');

/**
 * @brief Iterate through the provided string and return a set of substrings that were separated by one of the provided delimiters.
 * @param data The information to parse.
 * @param del A string of delimiters.  If any of the characters in this string is found then add that substring to the return set.
 * @return A set of substrings of the provided data separated by the provided delimiters.
 */
std::list<std::string> extractDataAsCollection(const std::string& data, const std::string& del);

/**
 * @brief Extract a filename from a full filename.
 * @param filename The filename of the file.
 * @return The name of the file (from the last backslash to the period of the extension).
 */
std::string extractFilename(const std::string& filename);

/**
 * @brief Format the string to fit in the provided width with the provided font.
 * @param string The text string to format.
 * @param font The font with which the string will be displayed.
 * @param width The width of the area into which the string must fit.
 * @return A copy of the formatted string.
 */
std::string formatStringToFit(std::string str, gcn::Font* font, const int width);

/**
 * @brief Determine's if a point is provided within the boundaries of a triangle defined by three points.
 * @param a The first point.
 * @param b The second point.
 * @param c The third point.
 * @param p The point to check.
 * @return True if the point is within the bounds of the triangle.
 */
bool isPointInTriangle(const Vector& a, const Vector& b, const Vector& c, const Vector& p);

/**
 * @brief Essentially takes the provided string and returns a new string that contains only the first two numbers.
 * @param time The time to convert.
 * @return The converted string to a time-comfortable format.
 * @note This function essentially takes the first two digits of the provided time.
 */
std::string convertToTimeFormat(const std::string& time);

/**
 * @brief Convert the provided value into a string that represents the time.
 * @param time The time, in ms.
 * @return The string value of the time.
 */
std::string convertToTime(unsigned int time);


#endif /* MAIN_HPP_ */
