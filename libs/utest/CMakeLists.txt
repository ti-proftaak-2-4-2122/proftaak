cmake_minimum_required(VERSION 3.21)

file(GLOB UTEST_SRC
        "src/*.cpp"
        "include/*.h"
        )

add_library(utest ${UTEST_SRC})