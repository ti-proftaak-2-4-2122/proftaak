cmake_minimum_required(VERSION 3.21)


file(GLOB ECS_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(ECS ${ECS_SRC})