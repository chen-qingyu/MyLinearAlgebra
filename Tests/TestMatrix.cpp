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

// append_row() append_col()
TEST(Matrix, append)
{
    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}).append_row(Matrix(2, 2, 0)), Matrix({{1, 2}, {3, 4}, {0, 0}, {0, 0}}));
    ASSERT_EQ(Matrix({{1, 2, 3, 4, 5}}).append_row(Matrix({{6, 7, 8, 9, 10}})), Matrix({{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}}));

    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}).append_col(Matrix(2, 2, 0)), Matrix({{1, 2, 0, 0}, {3, 4, 0, 0}}));
    ASSERT_EQ(Matrix({{1, 2, 3, 4, 5}}).append_col(Matrix({{6, 7, 8, 9, 10}})), Matrix({{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}));
}

// split_row() split_col()
TEST(Matrix, split)
{
    Matrix matrix = {{1, 2}, {3, 4}, {5, 6}};

    ASSERT_EQ(matrix.split_row(1).first, Matrix({{1, 2}}));
    ASSERT_EQ(matrix.split_row(1).second, Matrix({{3, 4}, {5, 6}}));

    ASSERT_EQ(matrix.split_col(1).first, Matrix({{1}, {3}, {5}}));
    ASSERT_EQ(matrix.split_col(1).second, Matrix({{2}, {4}, {6}}));
}

// operator+()
TEST(Matrix, addition)
{
    ASSERT_EQ(Matrix(2, 3, 1) + Matrix(2, 3, 2), Matrix(2, 3, 3));
    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}) + Matrix({{-1, -1}, {-1, -1}}), Matrix({{0, 1}, {2, 3}}));
}

// operator-()
TEST(Matrix, difference)
{
    ASSERT_EQ(Matrix(2, 3, 1) - Matrix(2, 3, 2), Matrix(2, 3, -1));
    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}) - Matrix({{-1, -1}, {-1, -1}}), Matrix({{2, 3}, {4, 5}}));
}

// operator*()
TEST(Matrix, entrywise)
{
    ASSERT_EQ(Matrix(2, 3, 1) * Matrix(2, 3, 2), Matrix(2, 3, 2));
    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}) * Matrix({{-1, -1}, {-1, -1}}), Matrix({{-1, -2}, {-3, -4}}));
}

// operator*()
TEST(Matrix, scalar_multiplication)
{
    ASSERT_EQ(Matrix(2, 3, 1) * 2, Matrix(2, 3, 2));
    ASSERT_EQ(Matrix({{1, 2}, {3, 4}}) * 3, Matrix({{3, 6}, {9, 12}}));

    ASSERT_EQ(2 * Matrix(2, 3, 1), Matrix(2, 3, 2));
    ASSERT_EQ(3 * Matrix({{1, 2}, {3, 4}}), Matrix({{3, 6}, {9, 12}}));

    ASSERT_EQ(3 * Matrix({{1, 2}, {3, 4}}) * 0.5, Matrix({{1.5, 3}, {4.5, 6}}));
}

// dot()
TEST(Matrix, dot)
{
    ASSERT_EQ(dot(Matrix(2, 2, 1), Matrix(2, 2, 2)), Matrix(2, 2, 4));
    ASSERT_EQ(dot(Matrix(1, 3, 1), Matrix(3, 1, 1)), Matrix(1, 1, 3));
    MY_ASSERT_THROW_MESSAGE(dot(Matrix(1, 3, 1), Matrix(1, 3, 1)), std::runtime_error, "Error: The dimensions mismatch.");
}
