#include "Utils.hpp"

/**
 * @brief Change console colors
 * 
 * @param text 
 * @param color 
 * @return std::string 
 */
std::string Utils::colorify(std::string text, std::string color) {
    return color + text + "\033[0m";
}