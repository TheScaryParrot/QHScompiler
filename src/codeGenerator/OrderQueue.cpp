#pragma once

#include <memory>
#include <vector>

#include "Order.cpp"

class OrderQueue
{
   public:
    struct Node
    {
        Order order = Order::Empty();
        Node* next;
        Node* prev;
    };

    OrderQueue() = default;
    OrderQueue(Order order) { this->Enqueue(order); }
    ~OrderQueue() { this->Clear(); }

    void Enqueue(Order order)
    {
        Node* newNode = new Node();
        newNode->order = order;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void EnqueueInFront(Order order)
    {
        Node* newNode = new Node();
        newNode->order = order;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    Order Dequeue()
    {
        if (IsEmpty()) return Order::Empty();

        Node* current = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        Order order = current->order;
        delete current;
        return order;
    }
    Order Front() { return this->head->order; }
    bool IsEmpty() { return this->head == nullptr; }
    void Clear()
    {
        while (!IsEmpty()) Dequeue();
    }

    Node* GetHead() { return this->head; }

    std::string ToString()
    {
        std::string str = "";

        Node* current = head;

        while (current != nullptr)
        {
            str += current->order.ToString() + "\n";
            current = current->next;
        }

        return str;
    }

   private:
    Node* head = nullptr;
    Node* tail = nullptr;
};

class OrderQueueIterator
{
   private:
    std::shared_ptr<OrderQueue> queue;
    OrderQueue::Node* current;

   public:
    OrderQueueIterator(std::shared_ptr<OrderQueue> queue)
    {
        this->queue = queue;
        this->current = queue->GetHead();
    }

    Order GetNext()
    {
        if (current == nullptr) return Order::Empty();

        Order order = current->order;

        current = current->next;

        return order;
    }

    bool IsDone() { return current == nullptr; }
};