cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE VISION_SRC CONFIGURE_DEPENDS
        "src/*.cpp"
        "include/*.h")

add_library(vision ${VISION_SRC})