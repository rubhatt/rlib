add_library(ipc 
    rlib_ipclockinginterface.cpp
    rlib_sharedmemlocking.cpp
    )

# specify target includes
target_include_directories(ipc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

