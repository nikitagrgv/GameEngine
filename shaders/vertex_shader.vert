#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 ourPos;
out vec4 ourColor;
out vec2 ourTexCoord;

uniform mat4 uTransform;

void main()
{
    gl_Position = uTransform * aPos;

    ourPos = aPos;
    ourColor = aColor;
    ourTexCoord = aTexCoord;
}