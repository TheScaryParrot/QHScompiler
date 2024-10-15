#pragma once

#include <string>

namespace StringUtils
{

const char WHITESPACES[] = {' ', '\n', '\t'};

bool IsWhiteSpace(char character)
{
    for (char i : WHITESPACES)
    {
        if (character == i) return true;
    }

    return false;
}

bool IsOnlyWhitespaces(std::string string)
{
    for (auto it = string.begin(); it != string.end(); ++it)
    {
        if (!IsWhiteSpace(*it)) return false;
    }

    return true;
}
}  // namespace StringUtils