#version 330 core

uniform sampler2D tex;

in vec2 uv_coords;
out vec4 color;

void main() {
    color = texture(tex, uv_coords).rgba;
}
