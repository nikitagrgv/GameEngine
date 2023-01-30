cmake_minimum_required(VERSION 3.24)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/vendor
        ${CMAKE_SOURCE_DIR}/src
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
        src/engine/core/Engine.cpp
        src/engine/core/Engine.h
        src/engine/core/GameLogic.h
        src/ExampleGameLogic.cpp
        src/ExampleGameLogic.h
        src/engine/core/Input.cpp
        src/engine/core/Input.h
        src/engine/core/FileManager.cpp
        src/engine/core/FileManager.h
        src/engine/render/VertexBuffer.cpp
        src/engine/render/VertexBuffer.h
        src/engine/render/IndexBuffer.cpp
        src/engine/render/IndexBuffer.h
        src/engine/render/VertexArray.cpp
        src/engine/render/VertexArray.h
        src/engine/render/VertexBufferLayout.cpp
        src/engine/render/VertexBufferLayout.h
        src/engine/render/Shader.cpp
        src/engine/render/Shader.h
        src/engine/render/Renderer.h
        src/engine/render/Renderer.cpp
        src/engine/render/OpenGLUtils.h
        src/engine/render/Texture.h
        src/engine/render/Texture.cpp
        src/engine/core/Camera.cpp
        src/engine/core/Camera.h
        src/engine/core/MathUtils.h
        src/engine/core/events/Event.h
        src/engine/core/events/InputEvents.h
        src/engine/core/InputEnums.h
        src/engine/core/GLFWWatcher.cpp
        src/engine/core/GLFWWatcher.h
        src/engine/core/IdContainer.h
        src/engine/core/events/WindowEvents.h
        src/engine/core/InputEnums.cpp src/engine/mesh/Mesh.cpp src/engine/mesh/Mesh.h)

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
