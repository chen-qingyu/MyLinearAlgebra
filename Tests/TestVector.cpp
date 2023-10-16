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

// operator==() operator!=()
TEST(Vector, compare)
{
    Vector vector({1, 2, 3, 4, 5});

    // operator==
    Vector eq_vector({1, 2, 3, 4, 5});
    ASSERT_TRUE(eq_vector == vector);

    // operator!=
    Vector ne_vector({1, 3, 5});
    ASSERT_TRUE(ne_vector != vector);
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

    // forward
    for (int i = 0; i < vector.size(); ++i)
    {
        ASSERT_EQ(vector[i], i + 1);
    }

    // assignment
    vector[0] = 0;
    ASSERT_EQ(vector[0], 0);

    ASSERT_THROW(vector[5], std::out_of_range);
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
    ASSERT_EQ(Vector().to_string(), "[]"); // string == char*, use eq

    ASSERT_EQ(Vector({1}).to_string(), "[1.000000]");

    ASSERT_EQ(Vector({1, 2, 3, 4, 5}).to_string(), "[1.000000, 2.000000, 3.000000, 4.000000, 5.000000]");
}

// operator+=()
TEST(Vector, append)
{
    Vector vector;

    // append element
    ASSERT_EQ(vector += 2, Vector({2}));
    ASSERT_EQ(vector += 3, Vector({2, 3}));
    ASSERT_EQ(vector += 3, Vector({2, 3, 3}));
    ASSERT_EQ(vector += 3, Vector({2, 3, 3, 3}));
    ASSERT_EQ(vector += 3, Vector({2, 3, 3, 3, 3}));

    // append vector
    ASSERT_EQ(vector += vector, Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3}));
    ASSERT_EQ(vector += vector, Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3}));
    ASSERT_EQ(vector += Vector({0, 0}), Vector({2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 2, 3, 3, 3, 3, 0, 0}));
}
