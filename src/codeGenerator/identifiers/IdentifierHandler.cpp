#pragma once

#include "EnvironmentLinkedList.cpp"

/// @brief Simple static wrapper for the EnvironmentLinkedList
static class IdentifierHandler
{
   private:
    EnvironmentLinkedList* envList = new EnvironmentLinkedList();

   public:
    IdentifierHandler() { PushEnvironment(); }
    ~IdentifierHandler() { delete envList; }

    void PushEnvironment() { this->envList->PushEnvironment(new Environment()); }
    void PopEnvironment() { this->envList->PopEnvironment(); }

    void AddIdentifier(std::string& name, Identifier* identifier) { this->envList->AddIdentifier(name, identifier); }
    Identifier* GetIdentifier(std::string& name) { return this->envList->GetIdentifier(name); }
} IdentifierHandler;