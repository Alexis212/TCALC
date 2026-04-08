#ifndef VECTOR_WRAPPER_H_
#define VECTOR_WRAPPER_H_

#include <vector>


class VectorWrapper
{
    public:
        VectorWrapper() = default;
        inline void push(double value) { stack.push_back(value); };
        void print_top();

        void remove_top();
        void duply_top();
        void swap_top();
    private:
        std::vector<double> stack;
};

#endif // VECTOR_WRAPPER_H_
