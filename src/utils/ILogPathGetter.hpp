#pragma once

#include <string>

/// @brief Interface for getting the path where a log message was sent from
class ILogPathGetter
{
   public:
    virtual std::string GetLogPath() = 0;
};