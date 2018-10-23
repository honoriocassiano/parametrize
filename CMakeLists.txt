cmake_minimum_required(VERSION 2.8)
project(Parametrize)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
    "src/*.hpp"
    "src/*.h"
    "src/*.cpp"
    "src/*.c"
)

MESSAGE(abc ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})


add_executable(parametrize ${SOURCE_FILES})

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

target_link_libraries(parametrize ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
