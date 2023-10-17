#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <stdexcept>

namespace mla::utility
{

// Check whether the index is valid (begin <= pos < end).
static inline void check_bounds(int pos, int begin, int end)
{
    if (pos < begin || pos >= end)
    {
        throw std::runtime_error("Error: Index out of range.");
    }
}

// Check whether is not empty.
static inline void check_empty(int size)
{
    if (size == 0)
    {
        throw std::runtime_error("Error: The container is empty.");
    }
}

// Check whether there is any remaining capacity.
static inline void check_full(int size, int capacity)
{
    if (size >= capacity)
    {
        throw std::runtime_error("Error: The container has reached the maximum size.");
    }
}

// Swap the content of the two elements.
template <typename T>
static inline void swap(T& e1, T& e2)
{
    auto tmp = std::move(e1);
    e1 = std::move(e2);
    e2 = std::move(tmp);
}

// Check that two vectors are of the same size.
static inline void check_size(int s1, int s2)
{
    if (s1 != s2)
    {
        throw std::runtime_error("Error: Two vectors with different sizes.");
    }
}

} // namespace mla::utility

#endif // UTILITY_HPP
