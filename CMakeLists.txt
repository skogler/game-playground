cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME game-playground)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(LOG_DEBUG 1)
set(LOG_INFO 1)

project(${PROJECT_NAME})
set(PROJECT_SOURCE_DIR src/)
set(PROJECT_INCLUDE_DIR src/)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/utils/config.h.in"
    "${PROJECT_SOURCE_DIR}/utils/config.h"
    )
include_directories("${PROJECT_INCLUDE_DIR}")

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
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
    # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
    target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARY})
endif()

# boost
#set(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
find_package(Boost 1.49.0 REQUIRED system filesystem chrono thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

include_directories("/usr/include/glm")

IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
