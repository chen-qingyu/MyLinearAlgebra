#include "../Sources/Vector.h"

#include <gtest/gtest.h>

using namespace mla;

// constructor destructor size() is_empty()
TEST(Vector, basics)
{
    // Vector()
    Vector vector1;
    ASSERT_EQ(vector1.size(), 0);
}
