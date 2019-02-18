//
//  Physics.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 18.02.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Physics.hpp"

static graphics::Box *bouncybox = nullptr, *floorbox = nullptr;
static graphics::Shader *shader = nullptr, *const_shader = nullptr;
static float angle_x = 0, angle_y = 0;
static float x = 0, y = -2, z = 0;
static const uint8_t *keys;
float vel = 0.0f;
float acc = 0.00981f;
static float box_y = -5;

static void eventHandler(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        angle_x += (float) e.motion.yrel / 200.0f;
        angle_y -= (float) e.motion.xrel / 200.0f;
        if(angle_x < -M_PI / 2.0f) angle_x = -M_PI / 2.0f;
        if(angle_x > M_PI / 2.0f) angle_x = M_PI / 2.0f;
    }
}

void test::physics::init(graphics::Window *window) {
    graphics::Texture *texture = new graphics::Texture("assets/textures/cube/water.png");
    bouncybox = new graphics::Box(-1, box_y, -4, 2, 2, 2, texture);
    floorbox = new graphics::Box(-100, 2, -100, 200, 1, 200, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    shader = graphics::loadFromFiles("assets/shaders/wave.vert", "assets/shaders/test_textured.frag");
    const_shader = graphics::loadFromFiles("assets/shaders/test.vert", "assets/shaders/test.frag");
    window->addEventHandler(eventHandler);
    
    SDL_CaptureMouse(SDL_TRUE);
    SDL_SetWindowGrab(window->getWindow(), SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    keys = SDL_GetKeyboardState(nullptr);
}

void test::physics::render() {
    shader->bind();
    shader->uniformf("angle_x", angle_x);
    shader->uniformf("angle_y", angle_y);
    shader->uniformf("time", 0);
    shader->uniformf("pos", x, y, z);
    
    const_shader->bind();
    const_shader->uniformf("angle_x", angle_x);
    const_shader->uniformf("angle_y", angle_y);
    const_shader->uniformf("time", 0);
    const_shader->uniformf("pos", x, y, z);

    //bouncybox->applyTransformation(maths::translate3(0.01, 0, 0));
    if(box_y >= 0) {
        vel *= -0.95;
        box_y += vel;
        bouncybox->resetModelView();
        bouncybox->applyTransformation(maths::translate3(0, 5, 0));
    } else {
        bouncybox->applyTransformation(maths::translate3(0, vel, 0));
        box_y += vel;
        vel += acc;
    }
    
    bouncybox->render(shader);
    floorbox->render(const_shader);
    
    float speed = 0.2f;
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
    if(keys[SDL_SCANCODE_SPACE]) y -= speed;
    if(keys[SDL_SCANCODE_LSHIFT]) y += speed;
}
