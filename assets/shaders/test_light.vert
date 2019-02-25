#version 330 core

#define PI 3.1415926535f

#include "assets/shaders/util/matutil.glsl"
#include "assets/shaders/util/perlin.glsl"

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;

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
out vec3 normal;
out vec3 viewpos;

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
    vert_coords = (modelview * vec4(vert, 1)).xyz;
    viewpos = pos;
    
    mat4 tran = perspective * modelview * (rotate_x(angle_x) * rotate_y(angle_y));
    normal = (inverse(tran) * vec4(norm, 1)).xyz;

    vec4 curpos = vec4(vert, 1.0) - vec4(pos, 0.0) + vec4(0, n, 0, 0);
    position = tran * curpos;
    
    
    gl_Position = position;
}
