#version 330 core

#define PI 3.1415926535f
#define ANGLE (PI / 4.0f)

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 color;

uniform float angle;

out vec4 position;
out vec3 col;

mat4 translation1 = mat4(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 1,
                        0, 0, 0, 1);

mat4 translation2 = mat4(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, -1,
                        0, 0, 0, 1);

void main() {
    col = color;
    
    position = mat4(cos(angle), 0, -sin(angle), 0,
                    0, 1, 0, 0,
                    sin(angle), 0, cos(angle), 0,
                    0, 0, 0, 1) * mat4(
                                       1, 0, 0, 0,
                                       0, cos(ANGLE), -sin(ANGLE), 0,
                                       0, sin(ANGLE), cos(ANGLE), 0,
                                       0, 0, 0, 1) * vec4(vert, 1.0);
    gl_Position = position;
}
