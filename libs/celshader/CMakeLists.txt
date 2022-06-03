cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE CELSHADER_SRC CONFIGURE_DEPENDS
		"src/*.cpp"
		"include/*.h"
		"shaders/*.h")

add_library(CelShader ${CELSHADER_SRC})

target_link_libraries(CelShader tigl glad glm)
