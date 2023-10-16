cmake_minimum_required(VERSION 3.14)
project(MyLinearAlgebra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TestVector Tests/TestVector.cpp Sources/Vector.cpp)

target_link_libraries(
  TestVector
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestVector)
