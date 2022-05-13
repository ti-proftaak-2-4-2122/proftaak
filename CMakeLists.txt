cmake_minimum_required(VERSION 3.21)
project(Proftaak24)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "libs/opencv")

find_package(OpenCV REQUIRED)

link_directories("libs/glfw/lib-mingw-w64")
link_directories("libs/glm/glm")

include_directories("libs/glfw/include")
include_directories("libs/glad/include")
include_directories("libs/tigl/include")
include_directories("modules/ECS/include")
include_directories("modules/objLoader/include")
include_directories("modules/vision/include")
include_directories("libs/glm")

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(modules/ECS)
add_subdirectory(libs/glm)
add_subdirectory(modules/objLoader)

add_executable(${CMAKE_PROJECT_NAME} main.cpp libs/glad/glad.c libs/tigl/tigl.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} libglfw3.a )
target_link_libraries(${CMAKE_PROJECT_NAME} glm )
target_link_libraries(${CMAKE_PROJECT_NAME} opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs )
target_link_libraries(${CMAKE_PROJECT_NAME} objLoader)
target_link_libraries(${CMAKE_PROJECT_NAME} ECS)
target_link_libraries(${CMAKE_PROJECT_NAME} vision)

# Copy opencv dlls to build dir if not exists
message("-- Copy OpenCV Dll's to output directory")
file(
        COPY "libs/opencv/x64/mingw/bin/"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
