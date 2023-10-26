#include "Matrix.h"

#include "utility.hpp"

#include <algorithm> // std::sort

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

int Matrix::rank() const
{
    Matrix echelon = Matrix(*this).transform_row_echelon();
    int zeros = 0;
    for (const auto& r : echelon.rows_)
    {
        if (r.is_zero())
        {
            ++zeros;
        }
    }
    return row_size() - zeros;
}

Matrix& Matrix::append_row(const Matrix& matrix)
{
    utility::check_size(col_size(), matrix.col_size());

    rows_.insert(rows_.end(), matrix.rows_.begin(), matrix.rows_.end());
    return *this;
}

Matrix& Matrix::append_col(const Matrix& matrix)
{
    utility::check_size(row_size(), matrix.row_size());

    for (int i = 0; i < row_size(); i++)
    {
        rows_[i].append(matrix[i]);
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& matrix)
{
    utility::check_size(row_size(), matrix.row_size());
    utility::check_size(col_size(), matrix.col_size());

    for (int r = 0; r < row_size(); r++)
    {
        (*this)[r] += matrix[r];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
    utility::check_size(row_size(), matrix.row_size());
    utility::check_size(col_size(), matrix.col_size());

    for (int r = 0; r < row_size(); r++)
    {
        (*this)[r] -= matrix[r];
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& matrix)
{
    utility::check_size(row_size(), matrix.row_size());
    utility::check_size(col_size(), matrix.col_size());

    for (int r = 0; r < row_size(); r++)
    {
        (*this)[r] *= matrix[r];
    }
    return *this;
}

Matrix& Matrix::operator*=(const double c)
{
    for (int r = 0; r < row_size(); r++)
    {
        (*this)[r] *= c;
    }
    return *this;
}

Matrix& Matrix::E(int i, int j)
{
    utility::swap(rows_[i], rows_[j]);
    return *this;
}

Matrix& Matrix::E(int i, double k)
{
    rows_[i] *= k;
    return *this;
}

Matrix& Matrix::E(int i, int j, double k)
{
    rows_[i] += rows_[j] * k;
    return *this;
}

Matrix& Matrix::transform_row_echelon()
{
    // step 1: Gaussian elimination
    for (int i = 0; i < row_size(); ++i)
    {
        int j = 0;
        while (j < col_size() && rows_[i][j] == 0)
        {
            ++j;
        }
        for (int k = i + 1; k < row_size(); ++k)
        {
            if (j < col_size() && rows_[i][j] != 0)
            {
                E(k, i, -(rows_[k][j] / rows_[i][j]));
            }
        }
    }

    // step 2: Transform to the row echelon form. It's so elegant, I'm a genius haha.
    std::sort(rows_.begin(), rows_.end(), [](const Vector& v1, const Vector& v2) -> bool
              { return v1.count_leading_zeros() < v2.count_leading_zeros(); });

    return *this;
}

std::pair<Matrix, Matrix> Matrix::split_row(int n) const
{
    utility::check_bounds(n, 0, row_size());

    Matrix first, second;
    first.rows_.assign(rows_.begin(), rows_.begin() + n);
    second.rows_.assign(rows_.begin() + n, rows_.end());

    return std::make_pair(first, second);
}

std::pair<Matrix, Matrix> Matrix::split_col(int n) const
{
    utility::check_bounds(n, 0, col_size());

    Matrix first, second;
    first.rows_.resize(row_size());
    second.rows_.resize(row_size());
    for (int r = 0; r < row_size(); r++)
    {
        first.rows_[r].elements_.assign(rows_[r].begin(), rows_[r].begin() + n);
        second.rows_[r].elements_.assign(rows_[r].begin() + n, rows_[r].end());
    }

    return std::make_pair(first, second);
}

Matrix Matrix::transpose() const
{
    Matrix result(col_size(), row_size(), 0);

    for (int i = 0; i < row_size(); i++)
    {
        for (int j = 0; j < col_size(); j++)
        {
            result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
    return Matrix(a) += b;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
    return Matrix(a) -= b;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    return Matrix(a) *= b;
}

Matrix operator*(const Matrix& m, const double c)
{
    return Matrix(m) *= c;
}

Matrix operator*(const double c, const Matrix& m)
{
    return m * c;
}

Matrix dot(const Matrix& a, const Matrix& b)
{
    utility::check_size(a.col_size(), b.row_size());

    Matrix result(a.row_size(), b.col_size(), 0);
    Matrix mt = b.transpose();
    for (int r = 0; r < a.row_size(); r++)
    {
        for (int c = 0; c < b.col_size(); c++)
        {
            result[r][c] = dot(a[r], mt[c]);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    return os << matrix.to_string();
}

} // namespace mla
