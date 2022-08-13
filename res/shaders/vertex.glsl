#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textCoord;

out vec2 v_textCoord;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    v_textCoord = textCoord;
}