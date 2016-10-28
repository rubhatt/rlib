cmake_minimum_required(VERSION 2.8.12)

add_library(prob
    prob_bloomfilter.cpp
    prob_bitfield.cpp
    hash.cpp
    )

# specify target includes
target_include_directories(prob PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(prob PUBLIC cxx_constexpr)
