#pragma once

#include <queue>

template <class T>
class Queue
{
   public:
    void Enqueue(T item) { items.push(item); }

    T Dequeue()
    {
        T item = items.front();
        items.pop();
        return item;
    }

    T Front()
    {
        if (IsEmpty())
        {
            throw std::out_of_range("Queue is empty");
        }

        return items.front();
    }

    bool IsEmpty() { return items.empty(); }

    void Clear()
    {
        while (!IsEmpty())
        {
            Dequeue();
        }
    }

   private:
    std::queue<T> items;
};