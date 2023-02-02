cmake_minimum_required(VERSION 3.16)
project (augmenta-cpp-test)
add_executable(augmenta-cpp-test README.txt main.cpp OrderCache.cpp OrderCache.h)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(submodules/googletest)
add_subdirectory(tests)
enable_testing()
include(GoogleTest)
