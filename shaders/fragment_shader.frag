#version 330 core
in vec3 ourColor;

out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(ourColor, 1.0);
//    FragColor.x = FragColor.x * sin(time) / 2;
//    FragColor.y = FragColor.y * sin(time) / 2;
//    FragColor.z = FragColor.z * sin(time) / 2;
}