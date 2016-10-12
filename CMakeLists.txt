cmake_minimum_required(VERSION 2.8.12)

project(rlib)

add_subdirectory(prob)
add_subdirectory(test)
target_compile_features(prob PRIVATE cxx_constexpr)
