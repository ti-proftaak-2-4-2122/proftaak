cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE PREFABS_SRC CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h")

add_library(prefabs ${PREFABS_SRC})

#use this method to add library dependencies to another library
target_link_libraries(prefabs ECS)