#pragma once

#include "../../utils/Logger.cpp"
#include "../AbstractGenerator.cpp"
#include "../Order.cpp"
#include "../identifiers/IdentifierHandler.cpp"
#include "../instructions/InstructionHandler.cpp"

class ExecuteHandler
{
   private:
    void HandleLiteralCode(std::string code, AbstractGenerator* generator)
    {
        generator->AddToAssemblyCode(code);
        generator->IncrementPhase();
    }
    void HandleIdentifier(Identifier* identifier, AbstractGenerator* generator)
    {
        generator->PutInFront(identifier->GetQueue());
        generator->IncrementPhase();
    }
    void HandleInstruction(Instruction* instruction, AbstractGenerator* generator)
    {
        // Increment phase if the execute function want that
        if (instruction->Execute(generator))
        {
            generator->IncrementPhase();
        }
    }

   public:
    void Execute(AbstractGenerator* generator)
    {
        Order order = generator->GetCurrentOrder();

        switch (order.GetType())
        {
            case Order::LiteralCode:
            {
                HandleLiteralCode(order.GetName(), generator);
                break;
            }
            case Order::Identifier:
            {
                Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

                if (identifier == nullptr)
                {
                    Logger.Log("No Identifier found for " + order.GetName(), Logger.ERROR);
                    generator->IncrementPhase();
                    return;
                }

                HandleIdentifier(identifier, generator);
                break;
            }
            case Order::Instruction:
            {
                Instruction* instruction = InstructionHandler.GetInstruction(order.GetName());

                if (instruction == nullptr)
                {
                    Logger.Log("No Instruction found for #" + order.GetName(), Logger.ERROR);
                    generator->IncrementPhase();
                    return;
                }

                HandleInstruction(instruction, generator);
                break;
            }
        }

        // generator->IncrementPhase() is done by Handle Functions individually because specific Instructions might
        // not want to advance to the next Phase
    }
};