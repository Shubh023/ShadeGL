cmake_minimum_required(VERSION 3.16)
project(ShadeGL)

set(CMAKE_CXX_STANDARD 20)

# Add useful packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include Directories
include_directories(include ${OPENGL_INCLUDE_DIRS}  ${GLEW_LIBRARY})

set(SOURCE_FILES src/main.cpp src/Shader.cpp src/stb.cpp src/Camera.cpp src/VBO.cpp src/VAO.cpp src/EBO.cpp src/Texture.cpp src/Mesh.cpp include/models/floor.h include/models/skybox.h include/models/box.h include/models/rectangle.h)

# ShadeGL Executable
add_executable(ShadeGL ${SOURCE_FILES})

# Link Libraries
target_link_libraries(${PROJECT_NAME} -lGL -lGLU -lGLEW -lglfw -lpthread)
