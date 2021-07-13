cmake_minimum_required(VERSION 3.19)
project(ShadeGL)

set(CMAKE_CXX_STANDARD 20)

# Add useful packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include Directories
include_directories(include ${OPENGL_INCLUDE_DIRS}  ${GLEW_LIBRARY})

# ShadeGL Executable
add_executable(ShadeGL src/main.cpp include/ShadeGL.h src/Shader.cpp include/Shader.h)

# Link
target_link_libraries(${PROJECT_NAME} -lGL -lGLU -lGLEW -lglfw -lpthread)
