#version 330 core

#define PI 3.1415926535f

#include "assets/shaders/util/perlin.glsl"

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 color;

uniform float angle_x;
uniform float angle_y;
uniform vec3 pos;
uniform float time;

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

float n = 0.1;
float f = 100;
float fov = PI / 2.0;
float S = 1.0 / tan(fov / 2.0);
mat4 perspective = mat4(S, 0, 0, 0,
                        0, -16.0 / 9.0 * S, 0, 0,
                        0, 0, f / (n - f), -1,
                        0, 0, f * n / (n - f), 0);

void main() {
    col = color;
    
    /*float t = time / 5.0f;
    float r = 5.0f * noise(vec3(vert.xz / 20.0f, t));
    float g = 5.0f * noise(vec3(vert.xy / 20.0f, t));
    float b = 5.0f * noise(vec3(vert.yz / 20.0f, t));*/
    
    //col = vec3(r, g, b);
    //position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y))) * (vec4(vert, 1.0) - vec4(pos, 0)));
    
    vec4 curpos = vec4(vert, 1.0) - vec4(pos, 0.0);
    curpos = rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y)) * curpos;
    curpos = perspective * curpos;
    position = curpos;
    
    gl_Position = position;
}
