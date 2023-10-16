/**
 * @file Vector.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Vector class.
 * @version 0.1
 * @date 2023.10.16
 *
 * @copyright Copyright (c) 2023
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <utility> // std::initializer_list std::move
#include <vector>  // std::vector

namespace mla // My Linear Algebra
{

/**
 * @brief Vector class.
 */
class Vector
{
private:
    // Vector elements.
    std::vector<double> elements_;

public:
    /*
     * Constructor / Destructor
     */

    /**
     * @brief Construct a new vector object.
     */
    Vector();

    /**
     * @brief Construct a vector based on the given initializer list.
     *
     * @param il initializer list
     */
    Vector(const std::initializer_list<double>& il);

    /**
     * @brief Construct a vector with n identical elements.
     *
     * @param n number of elements
     * @param element the element
     */
    Vector(int n, double element);

    /**
     * @brief Copy constructor.
     *
     * @param that another vector
     */
    Vector(const Vector& that);

    /**
     * @brief Move constructor.
     *
     * @param that another vector
     */
    Vector(Vector&& that);

    /*
     * Examination (will not change the object itself)
     */

    /**
     * @brief Return the number of elements in the vetor.
     *
     * @return the number of elements in the vetor
     */
    int size() const;

    /**
     * @brief Return true if the vector contains no elements.
     *
     * @return true if the vector contains no elements
     */
    bool is_empty() const;
};

} // namespace mla

#endif // VECTOR_H
