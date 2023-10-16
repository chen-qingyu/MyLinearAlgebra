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

#include <ostream> // std::ostream
#include <string>  // std::string
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
     * Comparison
     */

    /**
     * @brief Check whether two vectors are equal.
     *
     * @param that another vector
     * @return true if two vectors are equal
     */
    bool operator==(const Vector& that) const;

    /**
     * @brief Check whether two vectors are not equal.
     *
     * @param that another vector
     * @return true if two vectors are not equal
     */
    bool operator!=(const Vector& that) const;

    /*
     * Assignment
     */

    /**
     * @brief Copy assignment operator.
     *
     * @param that another vector
     * @return self reference
     */
    Vector& operator=(const Vector& that);

    /**
     * @brief Move assignment operator.
     *
     * @param that another vector
     * @return self reference
     */
    Vector& operator=(Vector&& that);

    /*
     * Access
     */

    /**
     * @brief Return the reference to the element at the specified position.
     *
     * @param index index of the element to return
     * @return reference to the element at the specified position
     */
    double& operator[](int index);

    /**
     * @brief Return the const reference to element at the specified position.
     *
     * @param index index of the element to return
     * @return const reference to the element at the specified position
     */
    const double& operator[](int index) const;

    /*
     * Iterator
     */

    /**
     * @brief Return an iterator to the first element of the vector.
     *
     * @return iterator to the first element
     */
    std::vector<double>::iterator begin();

    /**
     * @brief Return a const iterator to the first element of the vector.
     *
     * @return const iterator to the first element
     */
    std::vector<double>::const_iterator begin() const;

    /**
     * @brief Return an iterator to the element following the last element of the vector.
     *
     * @return iterator to the element following the last element
     */
    std::vector<double>::iterator end();

    /**
     * @brief Return a const iterator to the element following the last element of the vector.
     *
     * @return const iterator to the element following the last element
     */
    std::vector<double>::const_iterator end() const;

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

    /**
     * @brief Return a string representing the vector.
     *
     * @return a string representing the vector
     */
    std::string to_string() const;

    /*
     * Manipulation (will change the object itself)
     */

    /**
     * @brief Append the specified element to the end of the vector.
     *
     * @param element element to be appended to the vector
     * @return self reference
     */
    Vector& operator+=(double element);

    /**
     * @brief Append the specified vector to the end of the vector.
     *
     * @param vector vector to be appended to the vector
     * @return self reference
     */
    Vector& operator+=(const Vector& vector);

    /*
     * Production (will produce new object)
     */
};

/*
 * Non-member functions
 */

std::ostream& operator<<(std::ostream& os, const Vector& vector);

} // namespace mla

#endif // VECTOR_H
