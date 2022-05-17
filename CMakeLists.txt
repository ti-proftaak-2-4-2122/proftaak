cmake_minimum_required(VERSION 3.21)
project(Proftaak24)

set(CMAKE_CXX_STANDARD 20)
set(OpenCV_DIR "libs/opencv")

find_package(OpenCV REQUIRED)

# Get All Modules
set(MODULES_DIR_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")
set(MODULE_LIST "")

FILE(GLOB MODULE_DIR_FILE_LIST RELATIVE ${MODULES_DIR_PATH} ${MODULES_DIR_PATH}/*)

FOREACH(MODULE_DIR_FILE ${MODULE_DIR_FILE_LIST})
    IF(IS_DIRECTORY "${MODULES_DIR_PATH}/${MODULE_DIR_FILE}")
        LIST(APPEND MODULE_LIST ${MODULE_DIR_FILE})
    ENDIF()
ENDFOREACH()

link_directories("libs/glfw/lib-mingw-w64")
link_directories("libs/glm/glm")

#external libaries .h files directory
include_directories("libs/glfw/include")
include_directories("libs/glad/include")
include_directories("libs/tigl/include")
include_directories("libs/opencv/include")
include_directories("libs/glm")
include_directories(${OpenCV_INCLUDE_DIRS})

#include modules
FOREACH(MODULE ${MODULE_LIST})
    include_directories(${MODULES_DIR_PATH}/${MODULE}/include)
ENDFOREACH()

#internal libaries .h files directory
add_subdirectory(libs/glm)

#add modules
message("-- Adding all modules in modules folder")
FOREACH(MODULE ${MODULE_LIST})
    message("       Added ${MODULE}")
    add_subdirectory(${MODULES_DIR_PATH}/${MODULE})
ENDFOREACH()

add_executable(${CMAKE_PROJECT_NAME} main.cpp libs/glad/glad.c libs/tigl/tigl.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} libglfw3.a )
target_link_libraries(${CMAKE_PROJECT_NAME} glm )
target_link_libraries(${CMAKE_PROJECT_NAME} ${MODULE_LIST} )
target_link_libraries(${CMAKE_PROJECT_NAME} opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs )

# Copy opencv dlls to build dir if not exists
message("-- Copy OpenCV Dll's to output directory")
file(
        COPY "libs/opencv/x64/mingw/bin/"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)