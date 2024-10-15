#pragma once

#include <iostream>
#include <string>

#include "ILogPathGetter.hpp"

static class Logger
{
   public:
    enum ELogTypes
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    void Log(std::string message, ELogTypes type)
    {
        if (!IsDebug && type == ELogTypes::DEBUG)
        {
            return;
        }

        std::cout << ConstructLogMessage(message, type) << "\n";
    }

    void SetDebug(bool debug) { IsDebug = debug; }
    bool IsDebugActive() { return IsDebug; }

    void SetLogPathGetter(ILogPathGetter* pathGetter) { logPathGetter = pathGetter; }

   private:
    std::string ConstructLogMessage(std::string message, ELogTypes type)
    {
        std::string result = "[" + GetLogTypeString(type) + "]";

        if (logPathGetter != nullptr)
        {
            result += "(" + logPathGetter->GetLogPath() + ")";
        }

        return result + " " + message;
    }
    std::string GetLogTypeString(ELogTypes type)
    {
        switch (type)
        {
            case ELogTypes::DEBUG:
                return "DEBUG";
            case ELogTypes::INFO:
                return "INFO";
            case ELogTypes::WARNING:
                return "WARNING";
            case ELogTypes::ERROR:
                return "ERROR";
        }

        return "";
    }

    bool IsDebug = false;

    ILogPathGetter* logPathGetter;
} Logger;