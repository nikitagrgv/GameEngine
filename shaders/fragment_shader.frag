#version 330 core
out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor.x = FragColor.x * sin(time) / 2;
    FragColor.y = FragColor.y * sin(time) / 2;
    FragColor.z = FragColor.z * sin(time) / 2;
}