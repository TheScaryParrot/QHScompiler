#pragma once

#include <fstream>

class OutputFile
{
   public:
    OutputFile(std::string filename) { file.open(filename); }
    ~OutputFile() { file.close(); }

    void Write(std::string text) { file << text; }

   private:
    std::ofstream file;
};