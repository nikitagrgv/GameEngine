#version 330 core

in vec3 ourPos;
in vec3 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform float uTime;
uniform sampler2D uTexture;
uniform sampler2D uTexture_2;

void main()
{
    FragColor = mix(texture(uTexture, ourTexCoord), texture(uTexture_2, ourTexCoord), 0.5) + vec4(ourColor, 1.0f) / 2;
    FragColor += vec4(sin(uTime), sin(uTime + 1.0f), sin(uTime + 2.0f), 1);
    FragColor += vec4(0.1, 0, 0, 1);
//    FragColor = texture(uTexture, ourTexCoord) + texture(uTexture_2, ourTexCoord);
}