#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace String
{

inline std::vector<std::string> splitString(const std::string& string, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(string);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

} // namespace String
