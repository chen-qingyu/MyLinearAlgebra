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

int Vector::size() const
{
    return (int)elements_.size();
}

bool Vector::is_empty() const
{
    return elements_.size() == 0;
}

} // namespace mla
