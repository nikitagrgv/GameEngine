#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vPos;
out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * aPos;

    vPos = aPos;
    vColor = aColor;
    vTexCoord = aTexCoord;
}