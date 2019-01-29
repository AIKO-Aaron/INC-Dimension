//
//  Cube.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 23.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Cube.hpp"

#define CUBE_SIZE 6
#define NUM_BLOCKS (CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
#define INDEX(x, y, z) (CUBE_SIZE * CUBE_SIZE * (z) + CUBE_SIZE * (y) + (x))

static graphics::Box **box = new graphics::Box*[NUM_BLOCKS];
static graphics::Shader *shader;
static float angle_x, angle_y;
static const uint8_t *keys;
static uint8_t *fetched = nullptr;

void eventHandler(SDL_Event e) {
    if(e.type == SDL_MOUSEMOTION) {
        if(e.button.button == SDL_BUTTON_LEFT) {
            angle_x += (float) e.motion.yrel / 50.0f;
            angle_y -= (float) e.motion.xrel / 50.0f;
        }
        // printf("Mouse motion %d, %d\n", e.motion.xrel, e.motion.yrel);
    }
}

void test::cube::init(graphics::Window *window) {
    for(int i = 0; i < NUM_BLOCKS; i++) {
        float x = 1.01f * (float) ((int) (i % CUBE_SIZE)) / (float) CUBE_SIZE - 0.5f;
        float y = -1.01f * (float) ((int) (i / CUBE_SIZE) % CUBE_SIZE) / (float) CUBE_SIZE + 0.5f;
        float z = 1.01f * (float) ((int) (i / (CUBE_SIZE * CUBE_SIZE))) / (float) CUBE_SIZE - 0.5f;
        box[i] = new graphics::Box(x, y, z, 1.0f / (float) CUBE_SIZE, 1.0f / (float) CUBE_SIZE, 1.0f / (float) CUBE_SIZE, ((i/CUBE_SIZE)%CUBE_SIZE) == 0 ? 0xFFFFFF : ((i/CUBE_SIZE)%CUBE_SIZE) == 1 ? 0x000000 : 0xFFFF00, (i%CUBE_SIZE) == 0 ? 0xFF0000 : (i%CUBE_SIZE) == 1 ? 0x000000 : 0xFF7F00, (i/(CUBE_SIZE * CUBE_SIZE)) == 0 ? 0x0000FF : (i/(CUBE_SIZE * CUBE_SIZE)) == 1 ? 0x000000 : 0x00FF00);
    }
    shader = graphics::loadFromFiles("assets/shaders/test.vert", "assets/shaders/test.frag");
    angle_x = M_PI * 8.0f / 2.0f - 0.4;
    angle_y = 0;
    
    window->addEventHandler(eventHandler);
    
    int amt;
    keys = SDL_GetKeyboardState(&amt);
    fetched = new uint8_t[amt];
}

void rotateX(bool reverted = false, int sliceNum = 0) {
    if(reverted) {
        uint32_t *tmp = box[sliceNum]->getColors();
        box[sliceNum]->setColors(box[INDEX(sliceNum, 0, CUBE_SIZE - 1)]->getColors(), true);
        box[INDEX(sliceNum, 0, CUBE_SIZE - 1)]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, CUBE_SIZE - 1)]->getColors(), true);
        box[INDEX(sliceNum, CUBE_SIZE - 1, CUBE_SIZE - 1)]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, 0)]->getColors(), true);
        box[INDEX(sliceNum, CUBE_SIZE - 1, 0)]->setColors(tmp, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(sliceNum, 0, 1 + i)]->getColors(); // Rotate center pieces
            box[INDEX(sliceNum, 0, 1 + i)]->setColors(box[INDEX(sliceNum, 1 + i, CUBE_SIZE - 1)]->getColors(), true);
            box[INDEX(sliceNum, 1 + i, CUBE_SIZE - 1)]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, 1 + i)]->getColors(), true);
            box[INDEX(sliceNum, CUBE_SIZE - 1, 1 + i)]->setColors(box[INDEX(sliceNum, 1 + i, 0)]->getColors(), true);
            box[INDEX(sliceNum, 1 + i, 0)]->setColors(tmp, true);
        }
    } else {
        uint32_t *tmp = box[sliceNum]->getColors();
        box[sliceNum]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, 0)]->getColors(), true);
        box[INDEX(sliceNum, CUBE_SIZE - 1, 0)]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, CUBE_SIZE - 1)]->getColors(), true);
        box[INDEX(sliceNum, CUBE_SIZE - 1, CUBE_SIZE - 1)]->setColors(box[INDEX(sliceNum, 0, CUBE_SIZE - 1)]->getColors(), true);
        box[INDEX(sliceNum, 0, CUBE_SIZE - 1)]->setColors(tmp, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(sliceNum, 0, 1 + i)]->getColors(); // Rotate center pieces
            box[INDEX(sliceNum, 0, 1 + i)]->setColors(box[INDEX(sliceNum, 1 + i, 0)]->getColors(), true);
            box[INDEX(sliceNum, 1 + i, 0)]->setColors(box[INDEX(sliceNum, CUBE_SIZE - 1, 1 + i)]->getColors(), true);
            box[INDEX(sliceNum, CUBE_SIZE - 1, 1 + i)]->setColors(box[INDEX(sliceNum, 1 + i, CUBE_SIZE - 1)]->getColors(), true);
            box[INDEX(sliceNum, 1 + i, CUBE_SIZE - 1)]->setColors(tmp, true);
        }
    }
}

void rotateY(bool reverted = false, int sliceNum = 0) {
    if(reverted) {
        uint32_t *tmp = box[CUBE_SIZE * sliceNum]->getColors();
        box[CUBE_SIZE * sliceNum]->setColors(box[INDEX(0, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
        box[INDEX(0, sliceNum, CUBE_SIZE - 1)]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
        box[INDEX(CUBE_SIZE - 1, sliceNum, CUBE_SIZE - 1)]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, 0)]->getColors(), false, true);
        box[INDEX(CUBE_SIZE - 1, sliceNum, 0)]->setColors(tmp, false, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(0, sliceNum, 1 + i)]->getColors(); // Rotate center pieces
            box[INDEX(0, sliceNum, 1 + i)]->setColors(box[INDEX(1 + i, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
            box[INDEX(1 + i, sliceNum, CUBE_SIZE - 1)]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, 1 + i)]->getColors(), false, true);
            box[INDEX(CUBE_SIZE - 1, sliceNum, 1 + i)]->setColors(box[INDEX(1 + i, sliceNum, 0)]->getColors(), false, true);
            box[INDEX(1 + i, sliceNum, 0)]->setColors(tmp, false, true);
        }
    } else {
        uint32_t *tmp = box[CUBE_SIZE * sliceNum]->getColors();
        box[CUBE_SIZE * sliceNum]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, 0)]->getColors(), false, true);
        box[INDEX(CUBE_SIZE - 1, sliceNum, 0)]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
        box[INDEX(CUBE_SIZE - 1, sliceNum, CUBE_SIZE - 1)]->setColors(box[INDEX(0, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
        box[INDEX(0, sliceNum, CUBE_SIZE - 1)]->setColors(tmp, false, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(0, sliceNum, 1 + i)]->getColors(); // Rotate center pieces
            box[INDEX(0, sliceNum, 1 + i)]->setColors(box[INDEX(1 + i, sliceNum, 0)]->getColors(), false, true);
            box[INDEX(1 + i, sliceNum, 0)]->setColors(box[INDEX(CUBE_SIZE - 1, sliceNum, 1 + i)]->getColors(), false, true);
            box[INDEX(CUBE_SIZE - 1, sliceNum, 1 + i)]->setColors(box[INDEX(1 + i, sliceNum, CUBE_SIZE - 1)]->getColors(), false, true);
            box[INDEX(1 + i, sliceNum, CUBE_SIZE - 1)]->setColors(tmp, false, true);
        }
    }
}

void rotateZ(bool reverted = false, int sliceNum = 0) {
    if(reverted) {
        uint32_t *tmp = box[CUBE_SIZE * CUBE_SIZE * sliceNum]->getColors();
        box[CUBE_SIZE * CUBE_SIZE * sliceNum]->setColors(box[INDEX(0, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
        box[INDEX(0, CUBE_SIZE - 1, sliceNum)]->setColors(box[INDEX(CUBE_SIZE - 1, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
        box[INDEX(CUBE_SIZE - 1, CUBE_SIZE - 1, sliceNum)]->setColors(box[INDEX(CUBE_SIZE - 1, 0, sliceNum)]->getColors(), false, false, true);
        box[INDEX(CUBE_SIZE - 1, 0, sliceNum)]->setColors(tmp, false, false, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(0, 1 + i, sliceNum)]->getColors(); // Rotate center pieces
            box[INDEX(0, 1 + i, sliceNum)]->setColors(box[INDEX(1 + i, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
            box[INDEX(1 + i, CUBE_SIZE - 1, sliceNum)]->setColors(box[INDEX(CUBE_SIZE - 1, 1 + i, sliceNum)]->getColors(), false, false, true);
            box[INDEX(CUBE_SIZE - 1, 1 + i, sliceNum)]->setColors(box[INDEX(1 + i, 0, sliceNum)]->getColors(), false, false, true);
            box[INDEX(1 + i, 0, sliceNum)]->setColors(tmp, false, false, true);
        }
    } else {
        uint32_t *tmp = box[CUBE_SIZE * CUBE_SIZE * sliceNum]->getColors();
        box[CUBE_SIZE * CUBE_SIZE * sliceNum]->setColors(box[INDEX(CUBE_SIZE - 1, 0, sliceNum)]->getColors(), false, false, true);
        box[INDEX(CUBE_SIZE - 1, 0, sliceNum)]->setColors(box[INDEX(CUBE_SIZE - 1, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
        box[INDEX(CUBE_SIZE - 1, CUBE_SIZE - 1, sliceNum)]->setColors(box[INDEX(0, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
        box[INDEX(0, CUBE_SIZE - 1, sliceNum)]->setColors(tmp, false, false, true);
        
        for(int i = 0; i < CUBE_SIZE - 2; i++) {
            tmp = box[INDEX(0, 1 + i, sliceNum)]->getColors(); // Rotate center pieces
            box[INDEX(0, 1 + i, sliceNum)]->setColors(box[INDEX(1 + i, 0, sliceNum)]->getColors(), false, false, true);
            box[INDEX(1 + i, 0, sliceNum)]->setColors(box[INDEX(CUBE_SIZE - 1, 1 + i, sliceNum)]->getColors(), false, false, true);
            box[INDEX(CUBE_SIZE - 1, 1 + i, sliceNum)]->setColors(box[INDEX(1 + i, CUBE_SIZE - 1, sliceNum)]->getColors(), false, false, true);
            box[INDEX(1 + i, CUBE_SIZE - 1, sliceNum)]->setColors(tmp, false, false, true);
        }
    }
}
void test::cube::render() {
    shader->bind();
    //angle_x += 0.01f;
    
    shader->uniformf("angle_x", angle_x); // For the whole shader
    shader->uniformf("angle_y", angle_y); // For the whole shader

    for(int i = 0; i < NUM_BLOCKS; i++) box[i]->render(shader);
    
    if(keys[SDL_SCANCODE_RIGHT]) {
        if(!fetched[SDL_SCANCODE_RIGHT]) {
            rotateX(keys[SDL_SCANCODE_LSHIFT], CUBE_SIZE - 1);
        }
        fetched[SDL_SCANCODE_RIGHT] = true;
    } else fetched[SDL_SCANCODE_RIGHT] = false;
    
    if(keys[SDL_SCANCODE_LEFT]) {
        if(!fetched[SDL_SCANCODE_LEFT]) {
            rotateX(keys[SDL_SCANCODE_LSHIFT], 0);
        }
        fetched[SDL_SCANCODE_LEFT] = true;
    } else fetched[SDL_SCANCODE_LEFT] = false;
    
    if(keys[SDL_SCANCODE_DOWN]) {
        if(!fetched[SDL_SCANCODE_DOWN]) {
            rotateY(keys[SDL_SCANCODE_LSHIFT], CUBE_SIZE - 1);
        }
        fetched[SDL_SCANCODE_DOWN] = true;
    } else fetched[SDL_SCANCODE_DOWN] = false;
    
    if(keys[SDL_SCANCODE_UP]) {
        if(!fetched[SDL_SCANCODE_UP]) {
            rotateY(keys[SDL_SCANCODE_LSHIFT], 0);
        }
        fetched[SDL_SCANCODE_UP] = true;
    } else fetched[SDL_SCANCODE_UP] = false;
    
    if(keys[SDL_SCANCODE_M]) {
        if(!fetched[SDL_SCANCODE_M]) {
            rotateZ(keys[SDL_SCANCODE_LSHIFT], CUBE_SIZE - 1);
        }
        fetched[SDL_SCANCODE_M] = true;
    } else fetched[SDL_SCANCODE_M] = false;
    
    if(keys[SDL_SCANCODE_N]) {
        if(!fetched[SDL_SCANCODE_N]) {
            rotateZ(keys[SDL_SCANCODE_LSHIFT], 0);
        }
        fetched[SDL_SCANCODE_N] = true;
    } else fetched[SDL_SCANCODE_N] = false;
}
