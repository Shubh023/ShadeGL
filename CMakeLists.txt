cmake_minimum_required(VERSION 3.19)
project(ShadeGL)

set(CMAKE_CXX_STANDARD 20)

# Add useful packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include Directories
include_directories(include ${OPENGL_INCLUDE_DIRS}  ${GLEW_LIBRARY})

set(SOURCE_FILES src/main.cpp src/Shader.cpp src/Camera.cpp src/VBO.cpp src/VAO.cpp src/EBO.cpp include/stb_image.h src/stb.cpp src/Texture.cpp include/Texture.h)

# ShadeGL Executable
add_executable(ShadeGL ${SOURCE_FILES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} -lGL -lGLU -lGLEW -lglfw -lpthread)
