#pragma once

#include <functional>

#include "../AbstractGenerator.cpp"
#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Instruction : public CommentProofable, public OrderQueueProofable
{
   private:
    std::function<bool(AbstractGenerator*)> executeFunction;

   public:
    Instruction(std::function<bool(AbstractGenerator*)> executeFunction, bool orderQueueProof, bool commentProof)
    {
        this->executeFunction = executeFunction;
        this->SetOrderQueueProof(orderQueueProof);
        this->SetCommentProof(commentProof);
    }

    /// @brief Calls the instructions execute function
    /// @return Whether the generator should Increment to the next Phase
    bool Execute(AbstractGenerator* generator) { return this->executeFunction(generator); }
};