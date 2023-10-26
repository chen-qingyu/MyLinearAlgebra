#include "Matrix.h"

#include "utility.hpp"

namespace mla
{

Matrix::Matrix()
    : rows_()
{
}

Matrix::Matrix(const std::initializer_list<Vector>& il)
{
    // the number of elements in each row needs to be equal
    for (const auto& row : il)
    {
        utility::check_size(row.size(), il.begin()->size());
    }

    rows_.insert(rows_.end(), il.begin(), il.end());
}

Matrix::Matrix(int row, int col, double element)
{
    for (int i = 0; i < row; i++)
    {
        rows_.insert(rows_.end(), Vector(col, element));
    }
}

Matrix::Matrix(const Matrix& that)
    : rows_(that.rows_)
{
}

Matrix::Matrix(Matrix&& that)
    : rows_(std::move(that.rows_))
{
}

int Matrix::row_size() const
{
    return (int)rows_.size();
}

int Matrix::col_size() const
{
    return row_size() == 0 ? 0 : rows_.begin()->size();
}

} // namespace mla
