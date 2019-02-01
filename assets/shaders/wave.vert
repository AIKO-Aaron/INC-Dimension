#version 330 core

#define PI 3.1415926535f

#include "assets/shaders/util/matutil.glsl"
#include "assets/shaders/util/perlin.glsl"

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;

uniform float angle_x;
uniform float angle_y;
uniform vec3 pos;
uniform float time;

out vec4 position;
out vec2 uv_coords;

float r = 1;
float l = -1;
float n = 1;
float f = 100;
float t = -1;
float b = 1;
mat4 perspective = mat4(2.0*n/(r-l), 0, (r+l)/(r-l), 0,
                        0, 2.0*n/(t-b), (t+b)/(t-b), 0,
                        0, 0, (f+n)/(n-f), 2.0*f*n/(n-f),
                        0, 0, -1, 0);

void main() {
    uv_coords = uv;
    
    position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y))) * (vec4(vert, 1.0) - vec4(0, 3.0f * noise(vec3(vert.xz / 10.0f , time / 10.0f)), 0, 0) - vec4(pos, 0)));
    //position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y))) * (vec4(vert, 1.0) - vec4(0, 1.0f * sin(0.133711f * vert.x + 0.12144f * time) * sin(0.867992f * vert.z + 0.2134f * time), 0, 0) - vec4(pos, 0)));
    gl_Position = position;
}
