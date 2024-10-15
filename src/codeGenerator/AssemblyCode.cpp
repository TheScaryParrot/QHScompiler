#pragma once

#include <string>

#include "../utils/Map.cpp"
#include "../utils/StringUtils.cpp"

class AssemblyCode
{
   public:
    void AddCode(std::string code)
    {
        if (currentSection == nullptr)
        {
            // If is all whitespaces just ignore it
            if (StringUtils::IsOnlyWhitespaces(code)) return;

            Logger.Log("AssemblyCode currentSection is nullptr, cannot AddCode:" + code +
                           ". Did you forget to call ChangeSection()?",
                       Logger::ERROR);
            return;
        }

        // Remove empty lines
        if (this->currentSection->back() == '\n' && code.front() == '\n')
        {
            if (code == "\n") return;

            code = code.substr(1);
        }

        *this->currentSection += code;
    }

    void AddSection(std::string& name) { sections.Set(name, ""); }
    bool HasSection(std::string& name) { return sections.Contains(name); }
    void ChangeSection(std::string& name) { currentSection = &sections.Get(name); }

    std::string GetCode()
    {
        std::string result = "";

        for (std::pair<std::string, std::string> sectionPair : sections)
        {
            result += sectionPair.second;
        }

        return result;
    }

    std::string ToString() { return GetCode(); }

   private:
    Map<std::string, std::string> sections;
    std::string* currentSection = nullptr;
};
