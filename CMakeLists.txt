cmake_minimum_required(VERSION 3.16)
project(OpenGL_Labs)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

set(FREEGLUT_ROOT "C:/Users/123/Downloads/glutek/freeglut")
set(GLEW_ROOT    "C:/Users/123/Downloads/glew-2.3.1")
set(GLM_ROOT     "C:/Users/123/Downloads/glm-1.0.3/glm")

add_executable(OpenGL_Labs
    src/main.cpp
    src/Engine.cpp
    src/Camera.cpp
    src/Object.cpp
    src/Cube.cpp
    src/BitmapHandler.cpp
    src/Shader.cpp
)

target_include_directories(OpenGL_Labs PRIVATE
    ${FREEGLUT_ROOT}/include
    ${GLEW_ROOT}/include
    ${GLM_ROOT}
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(OpenGL_Labs PRIVATE
    OpenGL::GL
    "${GLEW_ROOT}/lib/Release/x64/glew32.lib"
    "${FREEGLUT_ROOT}/lib/x64/freeglut.lib"
)