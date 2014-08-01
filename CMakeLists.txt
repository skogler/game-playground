cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME game-playground)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(LOG_DEBUG 1)
set(LOG_INFO 1)

project(${PROJECT_NAME})
set(PROJECT_SOURCE_DIR src/)
set(PROJECT_INCLUDE_DIR src/)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -std=c++11")

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

#Math library
target_link_libraries(${EXECUTABLE_NAME} m)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
target_link_libraries(${EXECUTABLE_NAME}   ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

PKG_SEARCH_MODULE(CEGUI REQUIRED CEGUI-0)
target_link_libraries(${EXECUTABLE_NAME} ${CEGUI_LIBRARIES})
include_directories(${CEGUI_INCLUDE_DIRS})
PKG_SEARCH_MODULE(CEGUIGL REQUIRED CEGUI-0-OPENGL3)
target_link_libraries(${EXECUTABLE_NAME} ${CEGUIGL_LIBRARIES})
include_directories(${CEGUIGL_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
endif()

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_PATH})
    target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARY})
endif()

#find_package(CEGUI REQUIRED)
#if (CEGUI_FOUND)
#    include_directories(${CEGUI_INCLUDE_DIR})
#    target_link_libraries(${EXECUTABLE_NAME} ${CEGUI_LIBRARIES})
#endif()

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


add_custom_target(run
    COMMAND ${EXECUTABLE_NAME}
    DEPENDS ${EXECUTABLE_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../..
)
