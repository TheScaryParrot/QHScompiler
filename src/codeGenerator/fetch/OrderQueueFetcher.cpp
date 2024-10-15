#pragma once

#include "../OrderQueue.cpp"
#include "IOrderFetcher.cpp"

class OrderQueueFetcher : public IOrderFetcher
{
   public:
    OrderQueueFetcher(std::shared_ptr<OrderQueue> queue) { this->queue = new OrderQueueIterator(queue); }
    virtual ~OrderQueueFetcher() { delete queue; }

    virtual Order Next() override
    {
        Order order = queue->GetNext();
        lastOrder = order;
        return order;
    }

    virtual bool IsEmpty() override { return queue->IsDone(); }

    virtual std::string GetLastOrderLog() override { return lastOrder.ToLogString(); }

   private:
    OrderQueueIterator* queue;

    Order lastOrder = Order::Empty();
};