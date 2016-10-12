
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(probtest
    prob_bitfield.t.cpp
    main.t.cpp
    )

target_link_libraries(probtest LINK_PUBLIC prob GTest::GTest)
