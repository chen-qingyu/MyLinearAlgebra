#include "../Sources/Vector.h"

#include <gtest/gtest.h>

using namespace mla;

// constructor destructor size() is_empty()
TEST(Vector, basics)
{
    // Vector()
    Vector vector1;
    ASSERT_EQ(vector1.size(), 0);
    ASSERT_TRUE(vector1.is_empty());

    // Vector(const std::initializer_list<double>& il)
    Vector vector2 = {1, 2, 3, 4, 5};
    ASSERT_EQ(vector2.size(), 5);
    ASSERT_FALSE(vector2.is_empty());

    // Vector(int n, double element)
    Vector vector3(99, 233);
    ASSERT_EQ(vector3.size(), 99);
    ASSERT_FALSE(vector3.is_empty());

    // Vector(const Vector& that)
    Vector vector4 = vector3;
    ASSERT_EQ(vector4.size(), 99);
    ASSERT_FALSE(vector4.is_empty());

    // Vector(Vector&& that)
    Vector vector5 = std::move(vector4);
    ASSERT_EQ(vector5.size(), 99);
    ASSERT_FALSE(vector5.is_empty());
    ASSERT_EQ(vector4.size(), 0);
    ASSERT_TRUE(vector4.is_empty());
}
