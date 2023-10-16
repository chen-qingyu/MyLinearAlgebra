#include "Vector.h"

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
    return elements_.at(index);
}

const double& Vector::operator[](int index) const
{
    return elements_.at(index);
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
    return elements_.size() == 0;
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
        s.append(", ");
    }
    return s;
}

Vector& Vector::operator+=(double element)
{
    elements_.push_back(element);
    return *this;
}

Vector& Vector::operator+=(const Vector& vector)
{
    elements_.insert(elements_.end(), vector.elements_.begin(), vector.elements_.end());
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    return os << vector.to_string();
}

} // namespace mla
