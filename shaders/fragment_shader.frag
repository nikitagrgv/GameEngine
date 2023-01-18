#version 330 core

in vec4 ourPos;
in vec4 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform float uTime;
uniform sampler2D uTexture;
uniform sampler2D uTexture_2;

vec4 mix2(vec4 col1, vec4 col2, float part)
{
    return col1 + col2 * part;
    // return mix(col1, col2, part);
}

void main()
{
    FragColor = mix2(texture(uTexture, ourTexCoord), texture(uTexture_2, ourTexCoord), 0.5f + sin(uTime) * 0.5f);
    // FragColor = mix(texture(uTexture, ourTexCoord*2), texture(uTexture_2, ourTexCoord), 0.5) + vec4(ourColor, 1.0f) / 2;
    // FragColor += vec4(0.1f * sin(uTime), 0.1f * sin(uTime + 1.0f), 0.1f * sin(uTime + 2.0f), 1);
    // FragColor += vec4(0.1, 0, 0, 1);
}