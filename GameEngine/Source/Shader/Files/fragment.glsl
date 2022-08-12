#version 330 core

in vec4 fragmentColors;

out vec4 FragColor;

void main()
{
    FragColor = fragmentColors; //vec4(1.0f, 0.5f, 0.2f, 1.0f);
}