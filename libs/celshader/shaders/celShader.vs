#version 330

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec3 a_normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat3 normalMatrix = mat3(1.0);

out vec3 position;
out vec4 color;
out vec3 normal;

void main()
{
    position = vec3(modelMatrix * vec4(a_position, 1));
    color = a_color;
    normal = normalMatrix * a_normal;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_position, 1);
}