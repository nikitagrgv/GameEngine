#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aNormal;

out vec4 vPos;
out vec2 vTexCoord;
out vec4 vNormal;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * aPos;

    vPos = aPos;
    vTexCoord = aTexCoord;
    vNormal = aNormal;
}