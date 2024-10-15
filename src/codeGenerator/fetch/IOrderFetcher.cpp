#pragma once

#include "../Order.cpp"

class IOrderFetcher
{
   public:
    virtual ~IOrderFetcher() = default;

    virtual Order Next() = 0;
    virtual bool IsEmpty() = 0;

    /// @brief Returns the string of the last order fetched which shall be used by the Logger
    virtual std::string GetLastOrderLog() = 0;
};