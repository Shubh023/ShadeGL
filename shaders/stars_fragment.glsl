#version 330 core

out vec4 FragColor;

uniform vec4 cubeColor;

uniform vec4 lightColor;

void main()
{
    FragColor = cubeColor;
}