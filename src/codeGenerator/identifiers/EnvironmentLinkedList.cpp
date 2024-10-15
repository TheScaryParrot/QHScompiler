#pragma once

#include "Environment.cpp"

class EnvironmentLinkedList
{
   private:
    typedef struct Node
    {
        Environment* environment;
        Node* next;
    } Node;

    Node* head;

   public:
    ~EnvironmentLinkedList()
    {
        while (head != nullptr)
        {
            PopEnvironment();
        }
    }

    void PushEnvironment(Environment* environment)
    {
        Node* node = new Node();
        node->environment = environment;
        node->next = head;
        head = node;
    }

    void PopEnvironment()
    {
        if (head == nullptr) return;

        Node* next = head->next;
        delete head->environment;
        delete head;
        head = next;
    }

    void AddIdentifier(std::string& name, Identifier* identifier)
    {
        head->environment->AddIdentifier(name, identifier);
    }

    Identifier* GetIdentifier(std::string& name)
    {
        Node* current = head;
        while (current != nullptr)
        {
            Identifier* identifier = current->environment->GetIdentifier(name);
            if (identifier != nullptr) return identifier;

            current = current->next;
        }

        return nullptr;
    }
};