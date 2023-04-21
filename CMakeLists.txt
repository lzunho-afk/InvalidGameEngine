cmake_minimum_required(VERSION 3.10)

project("invalid_game_engine"
  VERSION 0.1.0.0
  DESCRIPTION "A beautiful and invalid game engine"
  HOMEPAGE_URL "https://github.com/lzunho-afk/InvalidGameEngine"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE 1)

set(SOURCES
  "${PROJECT_SOURCE_DIR}/main.cpp"
  "${PROJECT_SOURCE_DIR}/mesh.cpp"
)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(OPENGL_VERSION_MAJOR 4)
set(OPENGL_VERSION_MINOR 6)

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

# GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# yaml-cpp 
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIRS})

# config
configure_file (
  "${PROJECT_SOURCE_DIR}/include/version.h.in"
  "${PROJECT_BINARY_DIR}/include/version.h"
)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.yml"
  "${PROJECT_BINARY_DIR}/config.yml"
  COPYONLY
)

# targets
add_executable(invalidengine ${SOURCES})
target_include_directories(invalidengine PUBLIC ${PROJECT_BINARY_DIR}/include)

# linking
target_link_libraries(invalidengine
  glfw
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLM_LIBRARIES}
  ${YAML_CPP_LIBRARIES}
)
