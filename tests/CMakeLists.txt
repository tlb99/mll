include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set_source_files_properties(
  matrix_test.cc
  cuda_matrix_test.cc
  PROPERTIES LANGUAGE CUDA
)

add_executable(
  matrix_test
  matrix_test.cc
  cuda_matrix_test.cc
)

set_property(TARGET matrix_test 
             PROPERTY CUDA_ARCHITECTURES 60) # 60 is the compute capability of the Jetson Nano 

target_link_libraries(
  matrix_test
  GTest::gtest_main
  cudart
)

include(GoogleTest)
gtest_discover_tests(matrix_test)