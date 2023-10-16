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
     * @brief Construct a new Vector object.
     */
    Vector();

    /*
     * Examination (will not change the object itself)
     */

    /**
     * @brief Return the number of elements in the vetor.
     *
     * @return the number of elements in the vetor
     */
    int size() const;
};

} // namespace mla

#endif // VECTOR_H
