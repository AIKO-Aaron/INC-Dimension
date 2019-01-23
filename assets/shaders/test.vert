#version 330 core

#define PI 3.1415926535f

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 color;

uniform float angle;

out vec4 position;
out vec3 col;

mat4 rotate_z(float angle) {
    return mat4(cos(angle), -sin(angle), 0, 0,
                sin(angle), cos(angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
}

mat4 rotate_y(float angle) {
    return mat4(cos(angle), 0, sin(angle), 0,
                0, 1, 0, 0,
                -sin(angle), 0, cos(angle), 0,
                0, 0, 0, 1);
}

mat4 rotate_x(float angle) {
    return mat4(1, 0, 0, 0,
                0, cos(angle), -sin(angle), 0,
                0, sin(angle), cos(angle), 0,
                0, 0, 0, 1);
}

mat4 translate(float x, float y, float z) {
    return mat4(1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1);
}

mat4 scale = mat4(1, 0, 0, 0,
                  0, 16.0/9.0, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);

float r = 1;
float l = -1;
float n = 1;
float f = 10;
float t = -1;
float b = 1;
mat4 perspective = mat4(2.0*n/(r-l), 0, (r+l)/(r-l), 0,
                        0, 2.0*n/(t-b), (t+b)/(t-b), 0,
                        0, 0, (f+n)/(n-f), 2.0*f*n/(n-f),
                        0, 0, -1, 0);

void main() {
    col = color;
    
    /**modelview = modelview * translate(0, 0, 1.5);
    modelview = modelview * rotate_x(angle);
    modelview = modelview * translate(0, 0, -0.5f);*/
    
    position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle / 4.0f) * rotate_x(angle)) * vec4(vert, 1.0));
    gl_Position = position;
}
