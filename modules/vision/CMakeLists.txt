cmake_minimum_required(VERSION 3.21)

file(GLOB VISION_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(vision ${VISION_SRC})