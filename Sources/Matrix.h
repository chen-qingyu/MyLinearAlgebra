/**
 * @file Matrix.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Matrix class.
 * @version 1.0
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
     * @brief Construct a matrix with row x col identical elements.
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
     * @brief Check whether two matrices are equal.
     *
     * @param that another matrix
     * @return true if two matrices are equal
     */
    bool operator==(const Matrix& that) const;

    /**
     * @brief Check whether two matrices are not equal.
     *
     * @param that another matrix
     * @return true if two matrices are not equal
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

    /**
     * @brief Calculate the rank of this matrix.
     *
     * @return the rank of this matrix
     */
    int rank() const;

    /*
     * Manipulation (will change the object itself)
     */

    /**
     * @brief Expand this matrix by rows.
     *
     * @param matrix another matrix
     * @return self reference
     */
    Matrix& append_row(const Matrix& matrix);

    /**
     * @brief Expand this matrix by columns.
     *
     * @param matrix another matrix
     * @return self reference
     */
    Matrix& append_col(const Matrix& matrix);

    /**
     * @brief Addition.
     *
     * @param matrix another matrix
     * @return self reference
     */
    Matrix& operator+=(const Matrix& matrix);

    /**
     * @brief Difference.
     *
     * @param matrix another matrix
     * @return self reference
     */
    Matrix& operator-=(const Matrix& matrix);

    /**
     * @brief Hadamard product (entrywise product).
     *
     * @param matrix another matrix
     * @return self reference
     */
    Matrix& operator*=(const Matrix& matrix);

    /**
     * @brief Scalar multiplication.
     *
     * @param c a number
     * @return self reference
     */
    Matrix& operator*=(const double c);

    /**
     * @brief Elementary Row Operations: Row Swap.
     *
     * @param i index of the first row
     * @param j index of the second row
     * @return self reference
     */
    Matrix& E(int i, int j);

    /**
     * @brief Elementary Row Operations: Scalar Multiplication.
     *
     * @param i index of the row
     * @param k multiplication factor
     * @return self reference
     */
    Matrix& E(int i, double k);

    /**
     * @brief Elementary Row Operations: Row Sum.
     *
     * @param i index of the row to be changed
     * @param j index of the row to be multiplied
     * @param k multiplication factor
     * @return self reference
     */
    Matrix& E(int i, int j, double k);

    /**
     * @brief Transform this matrix to general row echelon form.
     *
     * @return self reference
     */
    Matrix& transform_row_echelon();

    /*
     * Production (will produce new object)
     */

    /**
     * @brief Split this matrix by rows.
     *
     * @param n the row index
     * @return split matrix pair
     */
    std::pair<Matrix, Matrix> split_row(int n) const;

    /**
     * @brief Split this matrix by columns.
     *
     * @param n the column index
     * @return split matrix pair
     */
    std::pair<Matrix, Matrix> split_col(int n) const;

    /**
     * @brief Returns the transpose of the matrix.
     *
     * @return the transpose of the matrix
     */
    Matrix transpose() const;
};

/*
 * Arithmetic
 */

/**
 * @brief Return the addition of two matrices.
 *
 * @param a a matrix
 * @param b another matrix of the same size as a
 * @return the addition of two matrices
 */
Matrix operator+(const Matrix& a, const Matrix& b);

/**
 * @brief Return the difference of two matrices.
 *
 * @param a a matrix
 * @param b another matrix of the same size as a
 * @return the difference of two matrices
 */
Matrix operator-(const Matrix& a, const Matrix& b);

/**
 * @brief Return the Hadamard product (entrywise product) of two matrices.
 *
 * @param a a matrix
 * @param b another matrix of the same size as a
 * @return the Hadamard product (entrywise product) of two matrices
 */
Matrix operator*(const Matrix& a, const Matrix& b);

/**
 * @brief Return the scalar multiplication of matrix and number.
 *
 * @param m a matrix
 * @param c a number
 * @return the scalar multiplication of matrix and number
 */
Matrix operator*(const Matrix& m, const double c);

/**
 * @brief Return the scalar multiplication of matrix and number.
 *
 * @param c a number
 * @param m a matrix
 * @return the scalar multiplication of matrix and number
 */
Matrix operator*(const double c, const Matrix& m);

/**
 * @brief Return the product of two matrices.
 *
 * @param a a matrix (m rows, k cols)
 * @param b another matrix (k rows, n cols)
 * @return the product of two matrices (m rows, n cols)
 */
Matrix dot(const Matrix& a, const Matrix& b);

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
