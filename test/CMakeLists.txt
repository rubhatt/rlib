add_executable(test
    rlib_ipclockinginterface.t.cpp
    )

target_link_libraries(test LINK_PUBLIC ipc)
