#pragma once

#include <fstream>

class InputFile
{
   public:
    InputFile(std::string filename);
    ~InputFile();

    /// @brief Reads the next character from the file. And advances the file pointer.
    char ReadNext();

    /// @brief Peeks the next character from the file.
    char PeekNext();

    bool IsEndOfFile();
    bool IsGood();

   private:
    std::ifstream file;
};

InputFile::InputFile(std::string filename) { file.open(filename); }

InputFile::~InputFile() { file.close(); }

char InputFile::ReadNext() { return file.get(); }

char InputFile::PeekNext() { return file.peek(); }

bool InputFile::IsEndOfFile() { return file.eof(); }

bool InputFile::IsGood() { return file.good(); }