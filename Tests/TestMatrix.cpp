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
