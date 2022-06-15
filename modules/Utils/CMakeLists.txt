cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE MODULE_SRC CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h")

add_library(${MODULE} ${MODULE_SRC})

# Use this method to add library dependencies to another library
# Replace [Dependency] with the required module/libary name
#target_link_libraries(${MODULE} [Dependency])
target_link_libraries(${MODULE} ECS)