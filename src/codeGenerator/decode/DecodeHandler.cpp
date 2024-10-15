#pragma once

#include "../AbstractGenerator.cpp"
#include "../Order.cpp"
#include "../OrderQueue.cpp"
#include "../identifiers/IdentifierHandler.cpp"
#include "../instructions/InstructionHandler.cpp"

class DecodeHandler
{
   private:
    unsigned int orderQueueDepthCounter = 0;
    OrderQueue* queue;

    bool isInComment = false;

   public:
    DecodeHandler() { this->queue = new OrderQueue(); }
    ~DecodeHandler() { delete this->queue; }

    void Decode(AbstractGenerator* generator)
    {
        Order order = generator->GetCurrentOrder();

        bool isCommentProof = false;
        bool isOrderQueueProof = false;

        if (order.GetType() == Order::Identifier)
        {
            Identifier* identifier = IdentifierHandler.GetIdentifier(order.GetName());

            if (identifier != nullptr)
            {
                isCommentProof = identifier->IsCommentProof();
                isOrderQueueProof = identifier->IsOrderQueueProof();
            }
        }
        else if (order.GetType() == Order::Instruction)
        {
            Instruction* instruction = InstructionHandler.GetInstruction(order.GetName());

            if (instruction != nullptr)
            {
                isCommentProof = instruction->IsCommentProof();
                isOrderQueueProof = instruction->IsOrderQueueProof();
            }
        }

        if (isInComment)
        {
            if (isCommentProof)
            {
                generator->IncrementPhase();  // Continues to execute
                return;
            }

            generator->RestartCycle();  // Skips instruction
            return;
        }

        if (orderQueueDepthCounter > 0 && !isOrderQueueProof)
        {
            queue->Enqueue(order);
            generator->RestartCycle();  // Returns to beginning of GeneratorPhases loop
            return;
        }

        generator->IncrementPhase();
    }

    void IncrementOrderQueueDepthCounter() { this->orderQueueDepthCounter++; }
    void DecrementOrderQueueDepthCounter() { this->orderQueueDepthCounter--; }
    unsigned int GetOrderQueueDepth() { return this->orderQueueDepthCounter; }

    void EnterComment() { this->isInComment = true; }
    void ExitComment() { this->isInComment = false; }

    Order DequeueFromOrderQueue()
    {
        if (queue->IsEmpty())
        {
            Logger.Log("Cannot dequeue, OrderQueue is empty!", Logger.ERROR);
            return Order::Empty();
        }

        return queue->Dequeue();
    }

    void EnqueueInOrderQueue(Order order) { queue->Enqueue(order); }
    void EnqueueInOrderQueueFront(Order order) { queue->EnqueueInFront(order); }
    OrderQueue GetOrderQueueCopy() { return *queue; }
    OrderQueue* DequeueWholeOrderQueue()
    {
        OrderQueue* tmp = queue;
        this->queue = new OrderQueue();
        return tmp;
    }
};