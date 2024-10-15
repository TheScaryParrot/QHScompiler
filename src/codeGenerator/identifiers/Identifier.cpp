#pragma once

#include "../OrderQueue.cpp"
#include "../decode/CommentProofable.cpp"
#include "../decode/OrderQueueProofable.cpp"

class Identifier : public CommentProofable, public OrderQueueProofable
{
   private:
    std::shared_ptr<OrderQueue> queue;

   public:
    Identifier(OrderQueue* queue) { this->queue = std::shared_ptr<OrderQueue>(queue); }

    std::shared_ptr<OrderQueue> GetQueue() { return this->queue; }
};