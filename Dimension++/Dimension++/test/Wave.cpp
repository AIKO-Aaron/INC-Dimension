//
//  Wave.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Wave.hpp"

#define SQUARE_SIZE 16

static graphics::Shader *shader;
static graphics::Box **boxes = new graphics::Box*[SQUARE_SIZE * SQUARE_SIZE];
float angle_x = 0.0f, angle_y = 0.0f;
float x = 0, y = 0, z = 0;
float curTime = 0.0f;
static const uint8_t *keys;

static void eventHandler(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        angle_x += (float) e.motion.yrel / 200.0f;
        angle_y -= (float) e.motion.xrel / 200.0f;
        if(angle_x < -M_PI / 2.0f) angle_x = -M_PI / 2.0f;
        if(angle_x > M_PI / 2.0f) angle_x = M_PI / 2.0f;
    }
}

void test::wave::init(graphics::Window *window) {
    shader = graphics::loadFromFiles("assets/shaders/wave.vert", "assets/shaders/test_textured.frag");
    window->addEventHandler(eventHandler);
    graphics::Texture *t = new graphics::Texture("assets/textures/cube/water.png");
    for(int i = 0; i < SQUARE_SIZE * SQUARE_SIZE; i++) boxes[i] = new graphics::Box(i % SQUARE_SIZE - SQUARE_SIZE / 2, 1, -1-(i / SQUARE_SIZE), 1, 1, 1, t);
    
    SDL_CaptureMouse(SDL_TRUE);
    SDL_SetWindowGrab(window->getWindow(), SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    keys = SDL_GetKeyboardState(nullptr);
}

void test::wave::render() {
    shader->bind();
    shader->uniformf("angle_x", angle_x);
    shader->uniformf("angle_y", angle_y);
    shader->uniformf("time", curTime += 0.01f);
    shader->uniformf("pos", x, y, z);
    for(int i = 0; i < SQUARE_SIZE * SQUARE_SIZE; i++) boxes[i]->render(shader);
    
    float speed = 0.1f;
    if(keys[SDL_SCANCODE_W]) {
        z -= speed * cos(angle_y);
        x -= speed * sin(angle_y);
    }
    if(keys[SDL_SCANCODE_S]) {
        z += speed * cos(angle_y);
        x += speed * sin(angle_y);
    }
    if(keys[SDL_SCANCODE_D]) {
        x += speed * cos(angle_y);
        z -= speed * sin(angle_y);
    }
    if(keys[SDL_SCANCODE_A]) {
        x -= speed * cos(angle_y);
        z += speed * sin(angle_y);
    }
}
