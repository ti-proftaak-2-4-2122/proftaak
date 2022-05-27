cmake_minimum_required(VERSION 3.21)

file(GLOB UTEST_SRC
        "include/*.h"
        "src/*.cpp"
        )

add_library(utest ${UTEST_SRC})