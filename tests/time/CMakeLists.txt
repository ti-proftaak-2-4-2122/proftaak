cmake_minimum_required(VERSION 3.21)

set(TEST_TARGET_NAME "${PROJECT_TEST_NAME}_${TEST}")

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
        "*.cpp")

add_executable(${TEST_TARGET_NAME} ${TEST_SRC})
add_test(${TEST} ${TEST_TARGET_NAME})

target_link_libraries(${TEST_TARGET_NAME} utest)

# Use this method to add library dependencies to another library
# Replace [Dependency] with the required module/libary name
#target_link_libraries(${TEST_TARGET_NAME} [Dependency])

target_link_libraries(${TEST_TARGET_NAME} time)