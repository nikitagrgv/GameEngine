#version 330 core
in vec3 ourColor;
in vec3 ourPosition;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform float time;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    FragColor = mix(texture(ourTexture, ourTexCoord), texture(ourTexture2, ourTexCoord), 0.5);
//    FragColor = texture(ourTexture, ourTexCoord) + texture(ourTexture2, ourTexCoord);
}