cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER /opt/intel/oneapi/compiler/latest/linux/bin/icx)
set(CMAKE_CXX_COMPILER /opt/intel/oneapi/compiler/latest/linux/bin/icpx)

project(oneapi_prog)

add_definitions(-D_GLIBCXX_USE_TBB_PAR_BACKEND=0)

include_directories(include)

list(APPEND CMAKE_MODULE_PATH "/opt/intel/oneapi/compiler/latest/linux/cmake/SYCL/")
find_package(IntelDPCPP REQUIRED)


add_library(oneapiprog SHARED prog.cpp)
target_link_libraries(oneapiprog -lpthread -lm)

install(TARGETS oneapiprog
        EXPORT OneApiProgTargets
        LIBRARY DESTINATION oneapiprog
        ARCHIVE DESTINATION oneapiprog
        )