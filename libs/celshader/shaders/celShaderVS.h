//
// Created by twanh on 3-6-2022.
//

#pragma once

#include <string>

std::string CEL_SHADER_VS_SRC = R"ESC(varying vec3 normal;
varying vec3 position;

void main()
{
	gl_FrontColor = gl_Color;
	normal = gl_NormalMatrix * gl_Normal;
	position = gl_ModelViewMatrix * gl_Vertex;

	gl_Position = ftransform();
}
)ESC";
