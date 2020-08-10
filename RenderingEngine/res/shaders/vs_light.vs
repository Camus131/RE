#version 450 core

out vec3 Pos;
out vec3 Normal;
out vec2 TexCoord;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 normal_model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Pos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(normal_model) * aNormal;
	TexCoord = aTexCoord;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}