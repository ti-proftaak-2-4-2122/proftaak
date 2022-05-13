cmake_minimum_required(VERSION 3.21)

file(GLOB OBJ_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(objLoader ${OBJ_SRC})