cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(LearnOpenGL src/main.cpp src/glad/glad.c src/Engine.cpp src/Engine.h src/GameLogic.h src/ExampleGameLogic.cpp src/ExampleGameLogic.h src/Input.cpp src/Input.h)

target_link_libraries(LearnOpenGL GLFW/glfw3 opengl32)
