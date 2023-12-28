/**
 * @file Vector.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Vector class.
 * @version 1.0
 * @date 2023.10.16
 *
 * @copyright Copyright (c) 2023
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <ostream> // std::ostream
#include <string>  // std::string
#include <utility> // std::initializer_list
#include <vector>  // std::vector

namespace mla
{

/**
 * @brief Vector class.
 */
class Vector
{
    friend class Matrix;

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
     * @brief Return the number of elements in the vector.
     *
     * @return the number of elements in the vector
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

    /**
     * @brief Calculate the length of the vector.
     *
     * @return the length of the vector
     */
    double length() const;

    /**
     * @brief Calculate the number of leading zeros for this vector.
     *
     * @return the number of leading zeros
     */
    int count_leading_zeros() const;

    /**
     * @brief Determine if it is a zero vector.
     *
     * @return true if it is a zero vector
     */
    bool is_zero() const;

    /*
     * Manipulation (will change the object itself)
     */

    /**
     * @brief Append the specified element to the end of the vector.
     *
     * @param element element to be appended to the vector
     * @return self reference
     */
    Vector& append(double element);

    /**
     * @brief Append the specified vector to the end of the vector.
     *
     * @param vector vector to be appended to the vector
     * @return self reference
     */
    Vector& append(const Vector& vector);

    /**
     * @brief Unitize this vector.
     *
     * @return self reference
     */
    Vector& unitize();

    /**
     * @brief Addition.
     *
     * @param vector another vector
     * @return self reference
     */
    Vector& operator+=(const Vector& vector);

    /**
     * @brief Difference.
     *
     * @param vector another vector
     * @return self reference
     */
    Vector& operator-=(const Vector& vector);

    /**
     * @brief Hadamard product (entrywise product).
     *
     * @param vector another vector
     * @return self reference
     */
    Vector& operator*=(const Vector& vector);

    /**
     * @brief Scalar multiplication.
     *
     * @param c a number
     * @return self reference
     */
    Vector& operator*=(const double c);
};

/*
 * Arithmetic
 */

/**
 * @brief Return the addition of two vectors.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return the addition of two vectors
 */
Vector operator+(const Vector& a, const Vector& b);

/**
 * @brief Return the difference of two vectors.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return the difference of two vectors
 */
Vector operator-(const Vector& a, const Vector& b);

/**
 * @brief Return the Hadamard product (entrywise product) of two vectors.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return the Hadamard product (entrywise product) of two vectors
 */
Vector operator*(const Vector& a, const Vector& b);

/**
 * @brief Return the scalar multiplication of vector and number.
 *
 * @param v non-empty vector
 * @param c a number
 * @return the scalar multiplication of vector and number
 */
Vector operator*(const Vector& v, const double c);

/**
 * @brief Return the scalar multiplication of vector and number.
 *
 * @param c a number
 * @param v non-empty vector
 * @return the scalar multiplication of vector and number
 */
Vector operator*(const double c, const Vector& v);

/**
 * @brief Return the dot product (scalar product, inner product) of two vectors.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return the dot product of two vectors
 */
double dot(const Vector& a, const Vector& b);

/**
 * @brief Return the cross product of two vectors.
 *
 * @param a a three dimensional vector
 * @param b a three dimensional vector
 * @return the cross product of two vectors.
 */
Vector cross(const Vector& a, const Vector& b);

/**
 * @brief Determine whether two vectors are orthogonal.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return true if the two vectors are orthogonal
 */
bool is_orthogonal(const Vector& a, const Vector& b);

/**
 * @brief Determine whether two vectors are paralle.
 *
 * @param a non-empty vector
 * @param b another vector of the same size as a
 * @return true if the two vectors are paralle
 */
bool is_parallel(const Vector& a, const Vector& b);

/*
 * Print
 */

/**
 * @brief Output vector data to the specified output stream.
 *
 * @param os an output stream
 * @param vector the vector to be printed to the output stream
 * @return self reference of the output stream
 */
std::ostream& operator<<(std::ostream& os, const Vector& vector);

} // namespace mla

#endif // VECTOR_H
