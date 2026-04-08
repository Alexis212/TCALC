#include "vector_wrapper.hpp"
#include <iostream>


void VectorWrapper::print_top()
{
    if (stack.empty())
        std::cout << "\n.\n";

    else
    {
        std::cout << "\n";
        int index = stack.size();

        for (auto item : stack)
        {
            std::cout << " " << index-- << ": " << item << "\n";
        }
    }
}

void VectorWrapper::remove_top()
{
    if (!stack.empty())
        stack.pop_back();

    else
        std::cout << "\nToo few arguments...\n";
}

void VectorWrapper::duply_top()
{
    if (!stack.empty())
        stack.push_back(stack.back());

    else
        std::cout << "\nToo few arguments...\n";
}

void VectorWrapper::swap_top()
{
    if (stack.size() >= 2)
    {
        double temp_1 = stack.back();
        stack.pop_back();
        double temp_2 = stack.back();
        stack.pop_back();
        stack.push_back(temp_1);
        stack.push_back(temp_2);
    }
}
