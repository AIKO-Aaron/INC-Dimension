//
//  Cube.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 23.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Cube.hpp"

graphics::Box **box = new graphics::Box*[3 * 9];
graphics::Shader *shader;
float angle;

const static char **textures = new const char*[1] {
    "assets/textures/cube/testcube.png"
};

void test::cube::init() {
    for(int i = 0; i < 27; i++) {
        graphics::Texture *texture = new graphics::Texture(textures[0]);
        
        float x = (float) ((int) (i % 3)) / 3.0f - 0.5f;
        float y = (float) ((int) (i / 3) % 3) / 3.0f - 0.5f;
        float z = (float) ((int) (i / 9)) / 3.0f - 0.5f;
        box[i] = new graphics::Box(x, y, z, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f, texture);
    }
    shader = graphics::loadFromFiles("assets/shaders/test_textured.vert", "assets/shaders/test_textured.frag");
    shader->uniformi("tex", 0);
    angle = 0;
}

void test::cube::render() {
    shader->bind();
    shader->uniformf("angle", angle);
    angle += 0.01f;
    for(int i = 0; i < 27; i++) box[i]->render(); // They use the same shader, so no problem
    shader->unbind();
}
