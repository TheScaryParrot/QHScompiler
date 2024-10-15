#pragma once

#include <string>

class Order
{
   public:
    enum EOrderTypes
    {
        Identifier,
        Instruction,
        LiteralCode
    };

    Order(Order const& order)
    {
        this->name = order.name;
        this->type = order.type;
        this->line = order.line;
    }

    Order(std::string* name, EOrderTypes type, unsigned int line)
    {
        this->name = name;
        this->type = type;
        this->line = line;
    }

    Order(std::string name, EOrderTypes type, unsigned int line)
    {
        this->name = new std::string(name);
        this->type = type;
        this->line = line;
    }

    std::string& GetName() { return *this->name; }
    EOrderTypes GetType() { return this->type; }
    unsigned int GetLine() { return this->line; }

    std::string ToString()
    {
        std::string result = GetName() + "{" + std::to_string(line) + "}";

        switch (GetType())
        {
            case EOrderTypes::Identifier:
                break;
            case EOrderTypes::Instruction:
                result += " (Compiler Instruction)";
                break;
            case EOrderTypes::LiteralCode:
                result += " (Direct Code)";
                break;
        }

        return result;
    }

    std::string ToLogString() { return GetName() + "{" + std::to_string(line) + "}"; }

    static inline Order Empty() { return Order("EMPTY", EOrderTypes::Identifier, 0); }

   private:
    std::string* name;
    EOrderTypes type = EOrderTypes::Identifier;
    unsigned int line;
};