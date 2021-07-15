#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;

layout (location = 2) in vec3 aColor;

layout (location = 3) in vec2 aTex;

out vec3 current_position;

out vec3 current_normal;

out vec3 color;

out vec2 texuv;

uniform mat4 camMatrix;

void main()
{

	current_position = vec3(vec4(aPos, 1.0f));

	current_normal = aNormal;

	color = aColor;
	texuv = aTex;

	gl_Position = camMatrix * vec4(current_position, 1.0);
}