#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_proj;
uniform mat4 u_model;
uniform mat4 u_view;

void main()
{
    gl_Position =  u_proj * u_view * u_model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}