/*
 * main.hpp
 *
 *  Created on: Mar 27, 2009
 *      Author: alienjon
 */
#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <string>

// Game constants.
extern const unsigned int DEFAULT_SCREEN_HEIGHT;
extern const unsigned int DEFAULT_SCREEN_WIDTH;
extern const char* GAME_NAME;
extern const char* GAME_VERSION;
extern const char DELIMITER;

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
        return low;

    // Check to make sure the lower value is not higher than the high value.
    if(low > high)
    {
    	T temp = high;
    	high = low;
    	low = temp;
    }

    return rand() % (high - low + 1) + low;
}

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
 * @brief Convert a string to lower-case.
 * @param str The string to convert.
 * @return A string of all lower-case characters.
 */
std::string toLower(const std::string& str);

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
 * @brief Essentially takes the provided string and returns a new string that contains only the first two numbers.
 * @param time The time to convert.
 * @return The converted string to a time-comfortable format.
 * @note This function essentially takes the first two digits of the provided time.
 */
std::string convertToTimeFormat(const std::string& time);

/**
 * @brief Convert the provided value into a string that represents the time.
 * @param time The time, in milliseconds.
 * @return The string value of the time.
 */
std::string convertToTime(unsigned int time);


#endif /* MAIN_HPP_ */
