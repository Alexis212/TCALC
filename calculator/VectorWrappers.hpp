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
    std::size_t size() const { return stack.size(); }
    bool is_empty() const { return stack.empty(); }
    const T& operator[](std::size_t index) const { return stack[index]; }

    void push(T value) { stack.push_back(value); }
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
class ObjectHistory
{
private:
    std::stack <T> undo_stack;
    std::stack <T> redo_stack;
public:
    ObjectHistory() = default;

    bool can_undo() { return !undo_stack.empty(); }
    bool can_redo() { return !redo_stack.empty(); }

    void save_state(T snapshot)
    {
        // Save current state in undo stack
        undo_stack.push(snapshot);

        // Clean redo stack
        redo_stack = std::stack<T>();
    }

    T undo(T snapshot)
    {
        if (!can_undo())
            throw std::out_of_range("Error: The undo stack is empty.");

        // Save current state in redo stack
        redo_stack.push(snapshot);

        // Get previous state
        T old_state = undo_stack.top();
        undo_stack.pop();

        // Set previous state
        return old_state;
    }

    T redo(T snapshot)
    {
        if (!can_redo())
            throw std::out_of_range("Error: The redo stack is empty.");

        // Get redo state
        T redo_state = redo_stack.top();
        redo_stack.pop();

        // Save current state into undo stack
        undo_stack.push(snapshot);

        // Set the new state
        return redo_state;
    }
};


class RNPCalc
{
private:
    IterableStack<double> stack;
    ObjectHistory <IterableStack <double>> history;
public:
    RNPCalc() = default;

    const IterableStack<double> &get_stack() const { return stack; };

    void insert(double value)
    {
        history.save_state(stack);
        stack.push(value);
    }

    void undo()
    {
        if (history.can_undo())
            stack = history.undo(stack);
    }

    void redo()
    {
        if (history.can_redo())
            stack = history.redo(stack);
    }
};

#endif // VECTORWRAPPERS_H_
