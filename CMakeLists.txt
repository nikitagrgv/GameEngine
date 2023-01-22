cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/vendor
)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(LearnOpenGL

        # imgui
        src/vendor/imgui/imconfig.h
        src/vendor/imgui/imgui_demo.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_internal.h
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui.h
        src/vendor/imgui/imstb_rectpack.h
        src/vendor/imgui/imstb_textedit.h
        src/vendor/imgui/imstb_truetype.h
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_impl_glfw.h
        src/vendor/imgui/imgui_impl_opengl3.h
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_opengl3_loader.h
        # end imgui

        src/main.cpp
        src/vendor/glad/glad.c
        src/core/Engine.cpp
        src/core/Engine.h
        src/core/GameLogic.h
        src/ExampleGameLogic.cpp
        src/ExampleGameLogic.h
        src/core/Input.cpp
        src/core/Input.h
        src/core/FileManager.cpp
        src/core/FileManager.h
        src/render/VertexBuffer.cpp
        src/render/VertexBuffer.h
        src/render/IndexBuffer.cpp
        src/render/IndexBuffer.h
        src/render/VertexArray.cpp
        src/render/VertexArray.h
        src/render/VertexBufferLayout.cpp
        src/render/VertexBufferLayout.h
        src/render/Shader.cpp
        src/render/Shader.h
        src/render/Renderer.h
        src/render/Renderer.cpp
        src/render/OpenGLUtils.h
        src/render/Texture.h
        src/render/Texture.cpp
        src/core/Camera.cpp
        src/core/Camera.h
        src/core/MathUtils.h)

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
