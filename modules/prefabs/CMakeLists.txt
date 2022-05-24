cmake_minimum_required(VERSION 3.21)

file(GLOB PREFABS_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(prefabs ${PREFABS_SRC})