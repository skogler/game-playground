cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME game-playground)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

project(${PROJECT_NAME})

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

configure_file(
  "${PROJECT_SOURCE_DIR}/src/utils/config.h.in"
  "${PROJECT_BINARY_DIR}/src/utils/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME ${PROJECT_NAME})

FILE(GLOB_RECURSE SRCFILES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SRCFILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()


# boost
#set(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
find_package(Boost 1.49.0 REQUIRED system filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

include_directories("/usr/include/glm")


