cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(LearnOpenGL
src/main.cpp
src/glad/glad.c
src/Engine.cpp
src/Engine.h
src/GameLogic.h
src/ExampleGameLogic.cpp
src/ExampleGameLogic.h
src/Input.cpp
src/Input.h
src/FileManager.cpp
src/FileManager.h
src/VertexBuffer.cpp
src/VertexBuffer.h
src/IndexBuffer.cpp
src/IndexBuffer.h
src/VertexArray.cpp
src/VertexArray.h
src/VertexBufferLayout.cpp
src/VertexBufferLayout.h
src/Shader.cpp
src/Shader.h

src/Render.h
)

target_link_libraries(LearnOpenGL GLFW/glfw3 opengl32)

set_target_properties(LearnOpenGL
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Application
        RUNTIME_OUTPUT_DIRECTORY_MinSizeRel ${CMAKE_SOURCE_DIR}/Application
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Application
        RUNTIME_OUTPUT_DIRECTORY_RelWithDebInfo ${CMAKE_SOURCE_DIR}/Application
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Application
        LIBRARY_OUTPUT_DIRECTORY_MinSizeRel ${CMAKE_SOURCE_DIR}/Application
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Application
        LIBRARY_OUTPUT_DIRECTORY_RelWithDebInfo ${CMAKE_SOURCE_DIR}/Application
        )
