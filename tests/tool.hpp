#ifndef TOOL_HPP
#define TOOL_HPP

#include <gtest/gtest.h>

#define MY_ASSERT_THROW_MESSAGE(expression, exception, message) \
    ASSERT_THROW(expression, exception);                        \
    try                                                         \
    {                                                           \
        expression;                                             \
    }                                                           \
    catch (const exception& e)                                  \
    {                                                           \
        ASSERT_STREQ(e.what(), message);                        \
    }

#endif // TOOL_HPP
