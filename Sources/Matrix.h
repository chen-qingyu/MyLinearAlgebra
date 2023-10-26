/**
 * @file Matrix.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Matrix class.
 * @version 0.1
 * @date 2023.10.26
 *
 * @copyright Copyright (c) 2023
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

namespace mla
{

/**
 * @brief Matrix class.
 */
class Matrix
{
private:
    // Each element is a row vector.
    std::vector<Vector> rows_;

public:
    /*
     * Constructor / Destructor
     */

    /**
     * @brief Construct a new matrix object.
     */
    Matrix();

    /**
     * @brief Construct a matrix based on the given initializer list.
     *
     * @param il initializer list
     */
    Matrix(const std::initializer_list<Vector>& il);

    /**
     * @brief Create a matrix with row x col identical elements.
     *
     * @param row number of rows
     * @param col number of columns
     * @param element fill element
     */
    Matrix(int row, int col, double element);

    /**
     * @brief Copy constructor.
     *
     * @param that another matrix
     */
    Matrix(const Matrix& that);

    /**
     * @brief Move constructor.
     *
     * @param that another matrix
     */
    Matrix(Matrix&& that);

    /*
     * Comparison
     */

    /**
     * @brief Check whether two matrixs are equal.
     *
     * @param that another matrix
     * @return true if two matrixs are equal
     */
    bool operator==(const Matrix& that) const;

    /**
     * @brief Check whether two matrixs are not equal.
     *
     * @param that another matrix
     * @return true if two matrixs are not equal
     */
    bool operator!=(const Matrix& that) const;

    /*
     * Assignment
     */

    /**
     * @brief Copy assignment operator.
     *
     * @param that another matrix
     * @return self reference
     */
    Matrix& operator=(const Matrix& that);

    /**
     * @brief Move assignment operator.
     *
     * @param that another matrix
     * @return self reference
     */
    Matrix& operator=(Matrix&& that);

    /*
     * Access
     */

    /**
     * @brief Return the reference to the row at the specified position.
     *
     * @param index index of the row to return
     * @return reference to the row at the specified position
     */
    Vector& operator[](int index);

    /**
     * @brief Return the const reference to row at the specified position.
     *
     * @param index index of the row to return
     * @return const reference to the row at the specified position
     */
    const Vector& operator[](int index) const;

    /*
     * Iterator
     */

    /**
     * @brief Return an iterator to the first row.
     *
     * @return iterator to the first row
     */
    std::vector<Vector>::iterator begin();

    /**
     * @brief Return a const iterator to the first row.
     *
     * @return const iterator to the first row
     */
    std::vector<Vector>::const_iterator begin() const;

    /**
     * @brief Return an iterator to the row following the last row.
     *
     * @return iterator to the row following the last row
     */
    std::vector<Vector>::iterator end();

    /**
     * @brief Return a const iterator to the row following the last row.
     *
     * @return const iterator to the row following the last row
     */
    std::vector<Vector>::const_iterator end() const;

    /*
     * Examination (will not change the object itself)
     */

    /**
     * @brief Return the number of rows in the matrix.
     *
     * @return the number of rows in the matrix
     */
    int row_size() const;

    /**
     * @brief Return the number of columns in the matrix.
     *
     * @return the number of columns in the matrix
     */
    int col_size() const;

    /**
     * @brief Return a string representing the matrix.
     *
     * @return a string representing the matrix
     */
    std::string to_string() const;

    /*
     * Manipulation (will change the object itself)
     */
};

/*
 * Arithmetic
 */

/*
 * Print
 */

/**
 * @brief Output matrix data to the specified output stream.
 *
 * @param os an output stream
 * @param matrix the matrix to be printed to the output stream
 * @return self reference of the output stream
 */
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

} // namespace mla

#endif // MATRIX_H
