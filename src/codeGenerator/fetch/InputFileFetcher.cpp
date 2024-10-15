#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "../../utils/InputFile.cpp"
#include "IOrderFetcher.cpp"

template <size_t N>
class CharacterGroup
{
   public:
    CharacterGroup(char characters[N]) { this->characters = characters; }

    bool IsCharacterInGroup(char character)
    {
        for (size_t i = 0; i < N; i++)
        {
            if (characters[i] == character)
            {
                return true;
            }
        }

        return false;
    }

   private:
    char* characters;
};

class InputFileFetcher : public IOrderFetcher
{
   public:
    InputFileFetcher(InputFile* file)
    {
        if (file == nullptr)
        {
            std::cerr << "Error: file is null" << std::endl;
        }

        this->file = file;
    }
    virtual ~InputFileFetcher() { delete file; }

    virtual Order Next() override
    {
        if (!file->IsGood())
        {
            std::cerr << "Error: file is not good" << std::endl;
            return Order::Empty();
        }

        ClearWhitespaces(file);

        char character = file->PeekNext();
        Order::EOrderTypes type = Order::Identifier;
        std::string name = "";

        if (directCode.IsCharacterInGroup(character))
        {
            file->ReadNext();
            character = file->PeekNext();
            type = Order::LiteralCode;

            while (!file->IsEndOfFile() && !directCode.IsCharacterInGroup(character))
            {
                // Increment line if linebreak inside of direct code
                if (linebreak.IsCharacterInGroup(character)) line++;

                file->ReadNext();
                name += character;
                character = file->PeekNext();
            }

            file->ReadNext();
            Order order(name, type, line);
            lastOrder = order;
            return order;
        }

        if (compilerInstruction.IsCharacterInGroup(character))
        {
            file->ReadNext();
            character = file->PeekNext();
            type = Order::Instruction;
        }

        while (!file->IsEndOfFile() && !whitespace.IsCharacterInGroup(character) &&
               !compilerInstruction.IsCharacterInGroup(character) && !directCode.IsCharacterInGroup(character))
        {
            file->ReadNext();
            name += character;
            character = file->PeekNext();
        }

        ClearWhitespaces(file);

        Order order(name, type, line);
        lastOrder = order;
        return order;
    }

    virtual bool IsEmpty() override { return file->IsEndOfFile(); }

    virtual std::string GetLastOrderLog() override { return lastOrder.ToLogString(); }

   private:
    void ClearWhitespaces(InputFile* file)
    {
        while (true)
        {
            if (file->IsEndOfFile()) return;

            if (linebreak.IsCharacterInGroup(file->PeekNext()))
            {
                line++;
                file->ReadNext();
                continue;
            }

            if (whitespace.IsCharacterInGroup(file->PeekNext()))
            {
                file->ReadNext();
                continue;
            }

            return;
        }
    }

    InputFile* file;

    char WHITESPACES[3] = {' ', '\n', '\t'};
    char LINEBREAK[1] = {'\n'};
    char COMPILER_INSTRUCTION[1] = {'#'};
    char DIRECT_CODE[1] = {'"'};

    CharacterGroup<3> whitespace = CharacterGroup<3>(WHITESPACES);
    CharacterGroup<1> linebreak = CharacterGroup<1>(LINEBREAK);
    CharacterGroup<1> compilerInstruction = CharacterGroup<1>(COMPILER_INSTRUCTION);
    CharacterGroup<1> directCode = CharacterGroup<1>(DIRECT_CODE);

    unsigned int line = 1;
    Order lastOrder = Order::Empty();
};