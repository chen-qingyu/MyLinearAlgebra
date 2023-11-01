#include "../Sources/Vector.h"

#include "tool.hpp"

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

// operator==() operator!=()
TEST(Vector, compare)
{
    Vector vector({1, 2, 3, 4, 5});

    // operator==
    ASSERT_TRUE(Vector({1, 2, 3, 4, 5}) == vector);

    // operator!=
    ASSERT_TRUE(Vector({1, 3, 5}) != vector);
}

// operator=()
TEST(Vector, copy_assignment)
{
    Vector vector1 = {1, 2, 3, 4, 5};
    Vector vector2 = {6, 7, 8, 9};

    vector1 = vector2;
    ASSERT_EQ(vector1, Vector({6, 7, 8, 9}));
    ASSERT_EQ(vector2, Vector({6, 7, 8, 9}));
}

// operator=()
TEST(Vector, move_assignment)
{
    Vector vector1 = {1, 2, 3, 4, 5};
    Vector vector2 = {6, 7, 8, 9};

    vector1 = std::move(vector2);
    ASSERT_EQ(vector1, Vector({6, 7, 8, 9}));
    ASSERT_EQ(vector2, Vector());
}

// operator[]()
TEST(Vector, access)
{
    Vector vector = {1, 2, 3, 4, 5};

    // for
    for (int i = 0; i < vector.size(); ++i)
    {
        ASSERT_EQ(vector[i], i + 1);
    }

    // assignment
    vector[0] = 0;
    ASSERT_EQ(vector[0], 0);

    // check bounds
    MY_ASSERT_THROW_MESSAGE(vector[5], std::runtime_error, "Error: Index out of range.");
}

// begin() end()
TEST(Vector, iterator)
{
    // empty
    Vector empty;
    ASSERT_EQ(empty.begin(), empty.end());

    Vector vector = {1, 2, 3, 4, 5};

    // for
    int i = 1;
    for (auto it = vector.begin(); it != vector.end(); ++it)
    {
        ASSERT_EQ(*it, i++);
    }

    // for in
    i = 1;
    for (const auto& e : vector)
    {
        ASSERT_EQ(e, i++);
    }
}

// to_string()
TEST(Vector, to_string)
{
    // empty vector
    ASSERT_EQ(Vector().to_string(), "[]"); // string == char*, use eq

    // one element
    ASSERT_EQ(Vector({1}).to_string(), "[1.000000]");

    // many elements
    ASSERT_EQ(Vector({1, 2, 3, 4, 5}).to_string(), "[1.000000 2.000000 3.000000 4.000000 5.000000]");
}

// length()
TEST(Vector, length)
{
    ASSERT_EQ(Vector({0}).length(), 0);
    ASSERT_EQ(Vector({1}).length(), 1);
    ASSERT_EQ(Vector({3, 4}).length(), 5);
}

// count_leading_zeros()
TEST(Vector, count_leading_zeros)
{
    ASSERT_EQ(Vector({0}).count_leading_zeros(), 1);
    ASSERT_EQ(Vector({0, 1}).count_leading_zeros(), 1);
    ASSERT_EQ(Vector({0, 0}).count_leading_zeros(), 2);
    ASSERT_EQ(Vector({0, 0, 1}).count_leading_zeros(), 2);
    ASSERT_EQ(Vector({0, 0, 0, 1, 2, 3}).count_leading_zeros(), 3);
}

// is_zero()
TEST(Vector, is_zero)
{
    ASSERT_TRUE(Vector({0}).is_zero());
    ASSERT_TRUE(Vector({0, 0, 0}).is_zero());

    ASSERT_FALSE(Vector({1}).is_zero());
    ASSERT_FALSE(Vector({0, 0, 1}).is_zero());
}

// append()
TEST(Vector, append)
{
    Vector vector;

    // append element
    ASSERT_EQ(vector.append(2), Vector({2}));
    ASSERT_EQ(vector.append(3), Vector({2, 3}));
    ASSERT_EQ(vector.append(3), Vector({2, 3, 3}));
    ASSERT_EQ(vector.append(3), Vector({2, 3, 3, 3}));
    ASSERT_EQ(vector.append(3), Vector({2, 3, 3, 3, 3}));

    // append vector
    ASSERT_EQ(vector.append(vector), Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3}));
    ASSERT_EQ(vector.append(vector), Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3}));
    ASSERT_EQ(vector.append({0, 0}), Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 0, 0}));
}

// unitize()
TEST(Vector, unitize)
{
    ASSERT_EQ(Vector({5}).unitize(), Vector({1}));
    ASSERT_EQ(Vector({1, 1}).unitize(), Vector({0.7071067811865475, 0.7071067811865475}));
    MY_ASSERT_THROW_MESSAGE(Vector({0}).unitize(), std::runtime_error, "Error: The zero vector can not be unitized.");
}

// operator+()
TEST(Vector, addition)
{
    ASSERT_EQ(Vector({1}) + Vector({1}), Vector({2}));
    ASSERT_EQ(Vector({1, 2, 3}) + Vector({4, 5, 6}), Vector({5, 7, 9}));
    ASSERT_EQ(Vector({1, 2}) + Vector({1, 2}) + Vector({1, 2}), Vector({3, 6}));
    MY_ASSERT_THROW_MESSAGE(Vector() + Vector(), std::runtime_error, "Error: The container is empty.");
    MY_ASSERT_THROW_MESSAGE(Vector({1}) + Vector({1, 2}), std::runtime_error, "Error: The dimensions mismatch.");
}

// operator-()
TEST(Vector, difference)
{
    ASSERT_EQ(Vector({1}) - Vector({1}), Vector({0}));
    ASSERT_EQ(Vector({1, 2, 3}) - Vector({4, 5, 6}), Vector({-3, -3, -3}));
    ASSERT_EQ(Vector({1, 2}) - Vector({1, 2}) - Vector({1, 2}), Vector({-1, -2}));
    MY_ASSERT_THROW_MESSAGE(Vector() - Vector(), std::runtime_error, "Error: The container is empty.");
    MY_ASSERT_THROW_MESSAGE(Vector({1}) - Vector({1, 2}), std::runtime_error, "Error: The dimensions mismatch.");
}

// operator*()
TEST(Vector, entrywise)
{
    ASSERT_EQ(Vector({1}) * Vector({1}), Vector({1}));
    ASSERT_EQ(Vector({1, 2, 3}) * Vector({4, 5, 6}), Vector({4, 10, 18}));
}

// operator*()
TEST(Vector, scalar_multiplication)
{
    ASSERT_EQ(Vector({1}) * 1, Vector({1}));
    ASSERT_EQ(Vector({1, 2, 3}) * 2, Vector({2, 4, 6}));
    ASSERT_EQ(Vector({1, 2}) * 2 * 0.4, Vector({0.8, 1.6}));

    ASSERT_EQ(1 * Vector({1}), Vector({1}));
    ASSERT_EQ(2 * Vector({1, 2, 3}), Vector({2, 4, 6}));
    ASSERT_EQ(2 * 0.4 * Vector({1, 2}), Vector({0.8, 1.6}));

    ASSERT_EQ(2 * Vector({1, 2}) * 4, Vector({8, 16}));

    MY_ASSERT_THROW_MESSAGE(Vector() * 1, std::runtime_error, "Error: The container is empty.");
}

// dot()
TEST(Vector, dot)
{
    ASSERT_EQ(dot(Vector({1}), Vector({1})), 1);
    ASSERT_EQ(dot(Vector({1, 2, 3}), Vector({4, 5, 6})), 32);
    MY_ASSERT_THROW_MESSAGE(dot(Vector(), Vector()), std::runtime_error, "Error: The container is empty.");
    MY_ASSERT_THROW_MESSAGE(dot(Vector({1}), Vector({1, 2})), std::runtime_error, "Error: The dimensions mismatch.");
}

// cross()
TEST(Vector, cross)
{
    ASSERT_EQ(cross(Vector({1, 2}), Vector({3, 4})), Vector({-2}));
    ASSERT_EQ(cross(Vector({1, 2, 3}), Vector({4, 5, 6})), Vector({-3, 6, -3}));
    MY_ASSERT_THROW_MESSAGE(cross(Vector({1}), Vector({1})), std::runtime_error, "Error: Incompatible dimensions for cross product.");
}

// is_orthogonal()
TEST(Vector, is_orthogonal)
{
    Vector zero = {0, 0};
    ASSERT_TRUE(is_orthogonal(zero, Vector({0, 0})));
    ASSERT_TRUE(is_orthogonal(zero, Vector({1, 1})));
    ASSERT_TRUE(is_orthogonal(zero, Vector({2, 3})));

    Vector one = {1, 1};
    ASSERT_TRUE(is_orthogonal(one, Vector({1, -1})));
    ASSERT_TRUE(is_orthogonal(one, Vector({-1, 1})));
    ASSERT_TRUE(is_orthogonal(one, Vector({-2, 2})));
}

// is_parallel()
TEST(Vector, is_parallel)
{
    Vector zero = {0, 0};
    ASSERT_TRUE(is_parallel(zero, Vector({0, 0})));
    ASSERT_TRUE(is_parallel(zero, Vector({1, 1})));
    ASSERT_TRUE(is_parallel(zero, Vector({2, 3})));

    Vector one = {3, 4};
    ASSERT_TRUE(is_parallel(one, Vector({3, 4})));
    ASSERT_TRUE(is_parallel(one, Vector({-3, -4})));
    ASSERT_TRUE(is_parallel(one, Vector({6, 8})));
}
