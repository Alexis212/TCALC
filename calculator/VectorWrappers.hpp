#ifndef VECTORWRAPPERS_H_
#define VECTORWRAPPERS_H_

#include <vector>
#include <stack>
#include <cstddef>
#include <stdexcept>


template<typename T>
class IterableStack
{
private:
    std::vector<T> stack;
public:
    IterableStack() = default;
    inline std::size_t size() const { return stack.size(); }
    inline bool is_empty() const { return stack.empty(); }
    const T& operator[](std::size_t index) const { return stack[index]; }

    inline void push(T value) { stack.push_back(value); }
    T pop()
    {
        if (is_empty())
            throw std::out_of_range("IterableStack::pop(): The stack is empty");

        T value = stack.back();
        stack.pop_back();
        return value;
    }
};


template <typename T>
class IterableStackHistory
{
private:
    IterableStack<T> stack;
    std::stack <IterableStack <T>> undo_stack;
    std::stack <IterableStack <T>> redo_stack;
public:
    IterableStackHistory() = default;

    // Adapted Interface
    inline std::size_t size() { return stack.size(); }
    inline bool is_empty() { return stack.is_empty(); }
    const T& operator[](int index) const { return stack[index]; }

    // New Methods
    void push(T value)
    {
        IterableStack<T> old_state = stack;
        undo_stack.push(old_state);
        stack.push(value);
    }

    T pop()
    {
        return stack.pop();
    }

    // New Data
    void undo()
    {
        IterableStack<T> current_state = stack;
        IterableStack<T> old_state = undo_stack.top();
        undo_stack.pop();
        redo_stack.push(current_state);
        stack = old_state;
    }

    void redo();
};

#endif // VECTORWRAPPERS_H_
