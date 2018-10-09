cmake_minimum_required(VERSION 2.8)
project(Parametrize)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.hpp"
    "src/*.h"
    "src/*.cpp"
    "src/*.c"
)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})


add_executable(picking ${SOURCE_FILES})

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

target_link_libraries(picking ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
