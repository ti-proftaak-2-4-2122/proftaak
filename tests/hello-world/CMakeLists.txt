cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
        "*.cpp")

add_executable(${PROJECT_TEST_NAME}_${TEST} ${TEST_SRC})
add_test(${TEST} ${PROJECT_TEST_NAME}_${TEST})