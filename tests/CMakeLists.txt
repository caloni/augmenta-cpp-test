cmake_minimum_required(VERSION 3.0.0)

project(augmenta-cpp-test-tests)

add_executable(augmenta-cpp-test-tests)
add_dependencies(augmenta-cpp-test-tests augmenta-cpp-test)
target_compile_features(augmenta-cpp-test-tests PUBLIC cxx_std_14)

target_include_directories(augmenta-cpp-test-tests PRIVATE
  ..
  ${gtest_SOURCE_DIR}/include
  ${gmock_SOURCE_DIR}/include
)

target_sources(augmenta-cpp-test-tests PRIVATE 
  augmenta-cpp-test-tests.cpp
)

target_link_libraries(augmenta-cpp-test-tests PRIVATE 
  gmock
  gtest
)

