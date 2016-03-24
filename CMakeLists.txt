cmake_minimum_required(VERSION 2.8.12)

project(rlib)

add_subdirectory(ipc)
add_subdirectory(test)
target_compile_features(ipc PRIVATE cxx_constexpr)
