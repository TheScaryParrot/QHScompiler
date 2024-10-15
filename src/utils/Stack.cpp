#pragma once

#include <stack>

template <class T>
class Stack
{
   public:
    void Push(T item) { stack.push(item); }

    T Pop()
    {
        T item = Top();
        stack.pop();
        return item;
    }

    T Top()
    {
        if (IsEmpty())
        {
            throw std::runtime_error("Stack is empty");
        }

        return stack.top();
    }

    bool IsEmpty() { return stack.empty(); }

   private:
    std::stack<T> stack;
};
