#include "../Sources/Matrix.h"

#include "tool.hpp"

using namespace mla;

// constructor destructor row_size() col_size()
TEST(Matrix, basics)
{
    // Matrix()
    Matrix matrix1;
    ASSERT_EQ(matrix1.row_size(), 0);
    ASSERT_EQ(matrix1.col_size(), 0);

    // Matrix(const std::initializer_list<Vector>& il)
    Matrix matrix2 = {{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(matrix2.row_size(), 2);
    ASSERT_EQ(matrix2.col_size(), 3);

    // Matrix(int row, int col, double element)
    Matrix matrix3(2, 3, 233);
    ASSERT_EQ(matrix3.row_size(), 2);
    ASSERT_EQ(matrix3.col_size(), 3);

    // Matrix(const Matrix& that)
    Matrix matrix4 = matrix3;
    ASSERT_EQ(matrix4.row_size(), 2);
    ASSERT_EQ(matrix4.col_size(), 3);

    // Matrix(Matrix&& that)
    Matrix matrix5 = std::move(matrix4);
    ASSERT_EQ(matrix5.row_size(), 2);
    ASSERT_EQ(matrix5.col_size(), 3);
    ASSERT_EQ(matrix4.row_size(), 0);
    ASSERT_EQ(matrix4.col_size(), 0);
}

// operator==() operator!=()
TEST(Matrix, compare)
{
    Matrix matrix({{1, 2, 3}, {4, 5, 6}});

    // operator==
    ASSERT_TRUE(Matrix({{1, 2, 3}, {4, 5, 6}}) == matrix);

    // operator!=
    ASSERT_TRUE(Matrix({{1, 2, 3}, {4, 5, 0}}) != matrix);
}

// operator=()
TEST(Matrix, copy_assignment)
{
    Matrix matrix1 = {{1, 2, 3}, {4, 5, 6}};
    Matrix matrix2 = {{2, 2}, {3, 3}};

    matrix1 = matrix2;
    ASSERT_EQ(matrix1, Matrix({{2, 2}, {3, 3}}));
    ASSERT_EQ(matrix2, Matrix({{2, 2}, {3, 3}}));
}

// operator=()
TEST(Matrix, move_assignment)
{
    Matrix matrix1 = {{1, 2, 3}, {4, 5, 6}};
    Matrix matrix2 = {{2, 2}, {3, 3}};

    matrix1 = std::move(matrix2);
    ASSERT_EQ(matrix1, Matrix({{2, 2}, {3, 3}}));
    ASSERT_EQ(matrix2, Matrix());
}

// operator[]()
TEST(Matrix, access)
{
    Matrix matrix = {{1, 2, 3}, {4, 5, 6}};

    // for
    for (int r = 0; r < matrix.row_size(); r++)
    {
        for (int c = 0; c < matrix.col_size(); c++)
        {
            ASSERT_EQ(matrix[r][c], r * 3 + c + 1);
        }
    }

    // assignment
    matrix[0][0] = 0;
    ASSERT_EQ(matrix[0][0], 0);

    // check bounds
    MY_ASSERT_THROW_MESSAGE(matrix[5][5], std::runtime_error, "Error: Index out of range.");
}

// begin() end()
TEST(Matrix, iterator)
{
    // empty
    Matrix empty;
    ASSERT_EQ(empty.begin(), empty.end());

    Matrix matrix = {{1, 2, 3}, {4, 5, 6}};

    // for
    for (auto it = matrix.begin(); it != matrix.end(); ++it)
    {
        ASSERT_EQ(it->size(), 3);
    }

    // for in
    for (const auto& e : matrix)
    {
        ASSERT_EQ(e.size(), 3);
    }
}

// to_string()
TEST(Matrix, to_string)
{
    // empty matrix
    ASSERT_EQ(Matrix().to_string(), "[]"); // string == char*, use eq

    // one element
    ASSERT_EQ(Matrix({{1}}).to_string(), "[1.000000]");

    // many elements
    ASSERT_EQ(Matrix({{1, 2, 3}, {4, 5, 6}}).to_string(), "[1.000000 2.000000 3.000000;\n 4.000000 5.000000 6.000000]");
}
