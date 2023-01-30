#version 330 core

in vec4 vPos;
in vec4 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform float uTime;
uniform sampler2D uTexture;
uniform sampler2D uTexture_2;

void main()
{
    FragColor = mix(texture(uTexture, vTexCoord), texture(uTexture_2, vTexCoord), 0.5f + sin(uTime * 2) * 0.2f);
    FragColor.w = 1;
}