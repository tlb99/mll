include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  matrix_test
  matrix_test.cc
)

target_link_libraries(
  matrix_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)