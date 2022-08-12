#version 330 core

in vec4 fragmentColors;

out vec4 FragColor;

uniform float ourColor;

void main()
{
    FragColor = vec4(fragmentColors.r, ourColor, fragmentColors.b, fragmentColors.a);
}