#pragma once

#include <functional>
#include <map>
#include <string>

#include "../../utils/Logger.cpp"
#include "Identifier.cpp"

class Environment
{
   public:
    ~Environment()
    {
        for (auto const& pair : identifiers)
        {
            delete pair.second;
        }
    }

    void AddIdentifier(std::string& name, Identifier* identifier)
    {
        // deletes existing identifier (delete nullptr is safe)
        delete GetIdentifier(name);

        identifiers[name] = identifier;
    }
    Identifier* GetIdentifier(std::string& name)
    {
        if (identifiers.find(name) == identifiers.end())
        {
            return nullptr;
        }

        return identifiers[name];
    }

   private:
    std::map<std::string, Identifier*> identifiers;
};