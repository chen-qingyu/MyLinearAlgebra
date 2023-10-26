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

bool Matrix::operator==(const Matrix& that) const
{
    if ((row_size() != that.row_size()) || (col_size() != that.col_size()))
    {
        return false;
    }

    for (int i = 0; i < row_size(); ++i)
    {
        if (rows_[i] != that.rows_[i])
        {
            return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& that) const
{
    return !(*this == that);
}

Matrix& Matrix::operator=(const Matrix& that)
{
    if (this != &that)
    {
        rows_ = that.rows_;
    }

    return *this;
}

Matrix& Matrix::operator=(Matrix&& that)
{
    if (this != &that)
    {
        rows_ = std::move(that.rows_);
    }

    return *this;
}

Vector& Matrix::operator[](int index)
{
    utility::check_bounds(index, 0, row_size());

    return rows_[index];
}

const Vector& Matrix::operator[](int index) const
{
    utility::check_bounds(index, 0, row_size());

    return rows_[index];
}

std::vector<Vector>::iterator Matrix::begin()
{
    return rows_.begin();
}

std::vector<Vector>::const_iterator Matrix::begin() const
{
    return rows_.cbegin();
}

std::vector<Vector>::iterator Matrix::end()
{
    return rows_.end();
}

std::vector<Vector>::const_iterator Matrix::end() const
{
    return rows_.cend();
}

int Matrix::row_size() const
{
    return (int)rows_.size();
}

int Matrix::col_size() const
{
    return row_size() == 0 ? 0 : rows_.begin()->size();
}

std::string Matrix::to_string() const
{
    if (rows_.empty())
    {
        return "[]";
    }

    auto it = rows_.begin();
    std::string s = "[";
    while (true)
    {
        std::string row = it->to_string();
        s.append(row.begin() + 1, row.end() - 1);
        ++it;
        if (it == rows_.end())
        {
            return s.append("]");
        }
        s.append(";\n ");
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    return os << matrix.to_string();
}

} // namespace mla
