//
//  Craft.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Craft.hpp"

static graphics::Box **boxes = new graphics::Box*[16 * 16 * 9]; // 16 by 16 blocks per chunk, 1 chunk we're in, 8 around
static graphics::Shader *shader;
static util::Random *_rand = new util::Random(0xC0FFEE);
static float angle_x = 0, angle_y = 0;
static float x = 0, y = 0, z = 0;
static const uint8_t *keys;

static void eventHandler(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        if(e.button.button == SDL_BUTTON_LEFT) {
            angle_x += (float) e.motion.yrel / 50.0f;
            angle_y -= (float) e.motion.xrel / 50.0f;
        }
        // printf("Mouse motion %d, %d\n", e.motion.xrel, e.motion.yrel);
    }
}

void test::craft::init(graphics::Window *window) {
    for(int i = 0; i < 1; i++) {
        for(int j = 0; j < 16 * 16; j++) {
            float x = (j % 16) - 8;
            float y = 4;
            float z = (int) (j / 16) - 8;
            boxes[i * 16 * 16 + j] = new graphics::Box(x, y, z, 1.0f, 1.0f, 1.0f, 0xFF000000 | _rand->randomInt(0xFFFFFF), 0xFFFF0000, 0xFF00FF00);
        }
    }
    
    SDL_CaptureMouse(SDL_TRUE);
    SDL_SetWindowGrab(window->getWindow(), SDL_TRUE);
    keys = SDL_GetKeyboardState(nullptr);
    window->addEventHandler(eventHandler);
    shader = graphics::loadFromFiles("assets/shaders/test.vert", "assets/shaders/test.frag");
}

void test::craft::render() {
    shader->bind();
    shader->uniformf("angle_x", angle_x);
    shader->uniformf("angle_y", angle_y);
    shader->uniformf("pos", x, y, z);
    
    for(int i = 0; i < 16 * 16; i++) {
        boxes[i]->render(shader);
    }
    
    if(keys[SDL_SCANCODE_W]) z -= 0.1f;
    if(keys[SDL_SCANCODE_S]) z += 0.1f;
    if(keys[SDL_SCANCODE_D]) x += 0.1f;
    if(keys[SDL_SCANCODE_A]) x -= 0.1f;
}
