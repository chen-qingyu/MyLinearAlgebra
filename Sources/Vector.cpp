#include "Vector.h"

namespace mla
{

Vector::Vector()
    : elements_()
{
}

int Vector::size() const
{
    return elements_.size();
}

} // namespace mla
