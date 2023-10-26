#include "Vector.h"

#include <climits> // INT_MAX
#include <cmath>   // std::sqrt

#include "utility.hpp"

namespace mla
{

Vector::Vector()
    : elements_()
{
}

Vector::Vector(const std::initializer_list<double>& il)
    : elements_(il)
{
}

Vector::Vector(int n, double element)
    : elements_(n, element)
{
}

Vector::Vector(const Vector& that)
    : elements_(that.elements_)
{
}

Vector::Vector(Vector&& that)
    : elements_(std::move(that.elements_))
{
}

bool Vector::operator==(const Vector& that) const
{
    return elements_ == that.elements_;
}

bool Vector::operator!=(const Vector& that) const
{
    return !(elements_ == that.elements_);
}

Vector& Vector::operator=(const Vector& that)
{
    if (this != &that)
    {
        elements_ = that.elements_;
    }

    return *this;
}

Vector& Vector::operator=(Vector&& that)
{
    if (this != &that)
    {
        elements_ = std::move(that.elements_);
    }

    return *this;
}

double& Vector::operator[](int index)
{
    utility::check_bounds(index, 0, size());

    return elements_[index];
}

const double& Vector::operator[](int index) const
{
    utility::check_bounds(index, 0, size());

    return elements_[index];
}

std::vector<double>::iterator Vector::begin()
{
    return elements_.begin();
}

std::vector<double>::const_iterator Vector::begin() const
{
    return elements_.cbegin();
}

std::vector<double>::iterator Vector::end()
{
    return elements_.end();
}

std::vector<double>::const_iterator Vector::end() const
{
    return elements_.cend();
}

int Vector::size() const
{
    return (int)elements_.size();
}

bool Vector::is_empty() const
{
    return elements_.empty();
}

std::string Vector::to_string() const
{
    if (elements_.empty())
    {
        return "[]";
    }

    auto it = elements_.begin();
    std::string s = "[";
    while (true)
    {
        s.append(std::to_string(*it++));
        if (it == elements_.end())
        {
            return s.append("]");
        }
        s.append(" ");
    }
    return s;
}

double Vector::length() const
{
    utility::check_empty(size());

    double result = 0;
    for (int i = 0; i < size(); i++)
    {
        result += elements_[i] * elements_[i];
    }
    return std::sqrt(result);
}

int Vector::count_leading_zeros() const
{
    utility::check_empty(size());

    int lz = 0;
    while (elements_[lz] == 0)
    {
        lz++;
        if (lz == size())
        {
            break;
        }
    }
    return lz;
}

bool Vector::is_zero() const
{
    return count_leading_zeros() == size();
}

Vector& Vector::append(double element)
{
    utility::check_full(size(), INT_MAX);

    elements_.push_back(element);
    return *this;
}

Vector& Vector::append(const Vector& vector)
{
    utility::check_full(size() + vector.size() - 1, INT_MAX);

    elements_.insert(elements_.end(), vector.elements_.begin(), vector.elements_.end());
    return *this;
}

Vector& Vector::unitize()
{
    utility::check_empty(size());

    if (is_zero())
    {
        throw std::runtime_error("Error: The zero vector can not be unitized.");
    }

    return *this = *this * (1.0 / length());
}

Vector& Vector::operator+=(const Vector& vector)
{
    utility::check_empty(size());
    utility::check_size(size(), vector.size());

    for (int i = 0; i < size(); i++)
    {
        (*this)[i] += vector[i];
    }
    return *this;
}

Vector& Vector::operator-=(const Vector& vector)
{
    utility::check_empty(size());
    utility::check_size(size(), vector.size());

    for (int i = 0; i < size(); i++)
    {
        (*this)[i] -= vector[i];
    }
    return *this;
}

Vector& Vector::operator*=(const Vector& vector)
{
    utility::check_empty(size());
    utility::check_size(size(), vector.size());

    for (int i = 0; i < size(); i++)
    {
        (*this)[i] *= vector[i];
    }
    return *this;
}

Vector& Vector::operator*=(const double c)
{
    utility::check_empty(size());

    for (int i = 0; i < size(); i++)
    {
        (*this)[i] *= c;
    }
    return *this;
}

Vector operator+(const Vector& a, const Vector& b)
{
    return Vector(a) += b;
}

Vector operator-(const Vector& a, const Vector& b)
{
    return Vector(a) -= b;
}

Vector operator*(const Vector& a, const Vector& b)
{
    return Vector(a) *= b;
}

Vector operator*(const Vector& v, const double c)
{
    return Vector(v) *= c;
}

Vector operator*(const double c, const Vector& v)
{
    return v * c;
}

double dot(const Vector& a, const Vector& b)
{
    utility::check_empty(a.size());
    utility::check_size(a.size(), b.size());

    double result = 0;
    for (int i = 0; i < a.size(); i++)
    {
        result += a[i] * b[i];
    }
    return result;
}

Vector cross(const Vector& a, const Vector& b)
{
    if (a.size() == 2 && b.size() == 2)
    {
        return Vector({a[0] * b[1] - a[1] * b[0]});
    }
    else if (a.size() == 3 && b.size() == 3)
    {
        return Vector({a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]});
    }
    else
    {
        throw std::runtime_error("Error: Incompatible dimensions for cross product.");
    }
}

bool is_orthogonal(const Vector& a, const Vector& b)
{
    utility::check_empty(a.size());
    utility::check_size(a.size(), b.size());

    return dot(a, b) == 0;
}

bool is_parallel(const Vector& a, const Vector& b)
{
    utility::check_empty(a.size());
    utility::check_size(a.size(), b.size());

    return std::abs(dot(a, b)) == a.length() * b.length();
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    return os << vector.to_string();
}

} // namespace mla
