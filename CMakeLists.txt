cmake_minimum_required(VERSION 3.16)
project(OpenGL_Labs)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

# ===== FREEGLUT =====
set(FREEGLUT_ROOT "C:/Users/wikto/Downloads/glutek")

add_executable(OpenGL_Labs
    src/main.cpp
    src/Engine.cpp
    src/Camera.cpp
    src/Cube.cpp
)

# Include directories
target_include_directories(OpenGL_Labs PRIVATE
    ${FREEGLUT_ROOT}/include
    C:/Users/wikto/Downloads/glm-master
)

# Link libraries (EXPLICITNIE plik .lib)
target_link_libraries(OpenGL_Labs PRIVATE
    OpenGL::GL
    "${FREEGLUT_ROOT}/lib/x64/freeglut.lib"
)
