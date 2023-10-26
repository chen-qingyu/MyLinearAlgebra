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
};

} // namespace mla

#endif // MATRIX_H
