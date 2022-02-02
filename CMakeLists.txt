cmake_minimum_required(VERSION 3.0.2)
project(ros_oneapi)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        std_msgs
        message_generation
        )

add_service_files(
        FILES
        vector.srv
)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
   CATKIN_DEPENDS roscpp
)


include_directories(
 ${catkin_INCLUDE_DIRS}
)

include(ExternalProject)
externalproject_add(oneapi_prog
        SOURCE_DIR ../../src/ros_oneapi/oneapi_prog
        CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CATKIN_PACKAGE_LIB_DESTINATION}"
        BUILD_ALWAYS 1
        )

include_directories(oneapi_prog/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/oneapi-prog-prefix/src/oneapi-prog-build)
add_library(oneapiprog SHARED IMPORTED)
set_target_properties(oneapiprog PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/oneapi_prog-prefix/src/oneapi_prog-build/liboneapiprog.so
        )

add_executable(vec_add_node src/vec_add_node.cpp)
target_link_libraries(vec_add_node
        ${catkin_LIBRARIES}
        oneapiprog
        )
add_dependencies(vec_add_node oneapi_prog)


