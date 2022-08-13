#version 330 core
layout (location = 0) out vec4 color;

uniform float ourColor;
uniform sampler2D ourText;
in vec2 v_textCoord;

void main()
{
//    FragColor = vec4(1.0f, ourColor, 0.2f, 1.0f);
    color = texture(ourText, v_textCoord) * vec4(1.0f, ourColor, 1.0f, 1.0f);
}