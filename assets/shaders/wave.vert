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
uniform mat4 modelview = mat4(1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              0,0,0,1);

out vec4 position;
out vec2 uv_coords;
out vec3 vert_coords;

float n = 0.1;
float f = 100;
float fov = PI / 2.0;
float S = 1.0 / tan(fov / 2.0);
mat4 perspective = mat4(S, 0, 0, 0,
                        0, -16.0 / 9.0 * S, 0, 0,
                        0, 0, f / (n - f), -1,
                        0, 0, f * n / (n - f), 0);

struct lightSource {
    vec3 position;
    vec4 color;
    float brightness;
    float maxRadius;
};

void main() {
    uv_coords = uv;
    
    //position = perspective * modelview * rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y)) * (vec4(vert, 1.0) - vec4(pos, 0));
    
    float n = 0;
    if(time != 0) n = noise(vec3(vert.xz / 10.0f , time / 10.0f));

    vert_coords = (modelview * vec4(vert + vec3(0, n, 0), 1)).xyz;

    vec4 curpos = vec4(vert, 1.0) - vec4(pos, 0.0) + vec4(0, n, 0, 0);
    curpos = rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y)) * curpos;
    curpos = perspective * modelview * curpos;
    position = curpos;

    
    // position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y))) * (vec4(vert, 1.0) - vec4(0, 3.0f * noise(vec3(vert.xz / 10.0f , time / 10.0f)), 0, 0) - vec4(pos, 0)));
    //position = perspective * (vec4(0, 0, -1.5, 0) + (rotate_y(angle_y) * rotate_z(-angle_x * sin(angle_y)) * rotate_x(angle_x * cos(angle_y))) * (vec4(vert, 1.0) - vec4(0, 1.0f * sin(0.133711f * vert.x + 0.12144f * time) * sin(0.867992f * vert.z + 0.2134f * time), 0, 0) - vec4(pos, 0)));
    gl_Position = position;
}
