/**
 * @note See source file for acknowledgements, etc...
 */

#ifndef BASE64_FUNC_HPP_
#define BASE64_FUNC_HPP_

#include <string>

/**
 * @brief Encode a data string to a base64 format.
 * @param data The data to encode.
 * @return A std::string representation of the data.
 */
std::string encodeBase64(const std::string& data);

/**
 * @brief Decode the base64 string.
 * @param data The base64 string to decode.
 * @return The decoded data.
 */
std::string decodeBase64(const std::string& data);

#endif
