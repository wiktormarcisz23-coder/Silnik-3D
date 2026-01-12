cmake_minimum_required(VERSION 3.16)
project(OpenGL_Labs)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

# ===== FREEGLUT =====
set(FREEGLUT_ROOT "C:/Users/wikto/Downloads/freeglut_OK")

include_directories(
    ${FREEGLUT_ROOT}/include
    C:/Users/wikto/Downloads/glm-master
)

link_directories(${FREEGLUT_ROOT}/lib/x64)

add_executable(OpenGL_Labs
    src/main.cpp
    src/Engine.cpp
    src/Camera.cpp
    src/Cube.cpp
)

target_link_libraries(OpenGL_Labs
    OpenGL::GL
    freeglut
)
