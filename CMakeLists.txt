cmake_minimum_required(VERSION 3.21)
project(Proftaak24)

set(CMAKE_CXX_STANDARD 20)

link_directories("libs/glfw/lib-mingw-w64")
link_directories("libs/glm/glm")

include_directories("libs/glfw/include")
include_directories("libs/glad/include")
include_directories("libs/tigl/include")
include_directories("libs/objLoader/include")
include_directories("libs/glm")
include_directories("libs/ECS/include")

add_subdirectory(libs/glm)
add_subdirectory(libs/objLoader)
add_subdirectory(libs/ECS)

add_executable(${CMAKE_PROJECT_NAME} main.cpp libs/glad/glad.c libs/tigl/tigl.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} libglfw3.a )
target_link_libraries(${CMAKE_PROJECT_NAME} glm )
target_link_libraries(${CMAKE_PROJECT_NAME} objLoader)
target_link_libraries(${CMAKE_PROJECT_NAME} ECS)
