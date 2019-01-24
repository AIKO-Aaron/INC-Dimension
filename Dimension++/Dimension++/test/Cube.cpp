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
const uint8_t *keys;
uint8_t *fetched = nullptr;

void test::cube::init() {
    for(int i = 0; i < 27; i++) {
        float x = 1.01f * (float) ((int) (i % 3)) / 3.0f - 0.5f;
        float y = -1.01f * (float) ((int) (i / 3) % 3) / 3.0f + 0.5f;
        float z = 1.01f * (float) ((int) (i / 9)) / 3.0f - 0.5f;
        box[i] = new graphics::Box(x, y, z, 1.0f / 3.0f, 1.0f / 3.0f, 1.0f / 3.0f, ((i/3)%3) == 0 ? 0xFFFFFF : ((i/3)%3) == 1 ? 0x000000 : 0xFFFF00, (i%3) == 0 ? 0xFF0000 : (i%3) == 1 ? 0x000000 : 0xFF7F00, (i/9) == 0 ? 0x0000FF : (i/9) == 1 ? 0x000000 : 0x00FF00);
    }
    shader = graphics::loadFromFiles("assets/shaders/test.vert", "assets/shaders/test.frag");
    angle = 0.0f;
    
    int amt;
    keys = SDL_GetKeyboardState(&amt);
    fetched = new uint8_t[amt];
}

void rotateRightSide(bool reverted = false) {
    if(reverted) {
        uint32_t* tmp = box[0 * 9 + 0 * 3 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 0 * 3 + 2]->setColors(box[2 * 9 + 0 * 3 + 2]->getColors(), true);
        box[2 * 9 + 0 * 3 + 2]->setColors(box[2 * 9 + 2 * 3 + 2]->getColors(), true);
        box[2 * 9 + 2 * 3 + 2]->setColors(box[0 * 9 + 2 * 3 + 2]->getColors(), true);
        box[0 * 9 + 2 * 3 + 2]->setColors(tmp, true);
        
        tmp = box[1 * 9 + 0 * 3 + 2]->getColors(); // Rotate center pieces
        box[1 * 9 + 0 * 3 + 2]->setColors(box[2 * 9 + 1 * 3 + 2]->getColors(), true);
        box[2 * 9 + 1 * 3 + 2]->setColors(box[1 * 9 + 2 * 3 + 2]->getColors(), true);
        box[1 * 9 + 2 * 3 + 2]->setColors(box[0 * 9 + 1 * 3 + 2]->getColors(), true);
        box[0 * 9 + 1 * 3 + 2]->setColors(tmp, true);
    } else {
        uint32_t* tmp = box[0 * 9 + 0 * 3 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 0 * 3 + 2]->setColors(box[0 * 9 + 2 * 3 + 2]->getColors(), true);
        box[0 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 2 * 3 + 2]->getColors(), true);
        box[2 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 0 * 3 + 2]->getColors(), true);
        box[2 * 9 + 0 * 3 + 2]->setColors(tmp, true);
        
        tmp = box[1 * 9 + 0 * 3 + 2]->getColors(); // Rotate center pieces
        box[1 * 9 + 0 * 3 + 2]->setColors(box[0 * 9 + 1 * 3 + 2]->getColors(), true);
        box[0 * 9 + 1 * 3 + 2]->setColors(box[1 * 9 + 2 * 3 + 2]->getColors(), true);
        box[1 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 1 * 3 + 2]->getColors(), true);
        box[2 * 9 + 1 * 3 + 2]->setColors(tmp, true);
    }
}

void rotateBottomSide(bool reverted = false) {
    if(reverted) {
        uint32_t* tmp = box[0 * 9 + 2 * 3 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 2 * 3 + 2]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 0]->setColors(box[0 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[0 * 9 + 2 * 3 + 0]->setColors(tmp, false, true);
        
        tmp = box[0 * 9 + 2 * 3 + 1]->getColors(); // Rotate center pieces
        box[0 * 9 + 2 * 3 + 1]->setColors(box[1 * 9 + 2 * 3 + 2]->getColors(), false, true);
        box[1 * 9 + 2 * 3 + 2]->setColors(box[2 * 9 + 2 * 3 + 1]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 1]->setColors(box[1 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[1 * 9 + 2 * 3 + 0]->setColors(tmp, false, true);
    } else {
        uint32_t* tmp = box[0 * 9 + 2 * 3 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 2 * 3 + 2]->setColors(box[0 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[0 * 9 + 2 * 3 + 0]->setColors(box[2 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 0]->setColors(box[2 * 9 + 2 * 3 + 2]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 2]->setColors(tmp, false, true);
        
        tmp = box[0 * 9 + 2 * 3 + 1]->getColors(); // Rotate center pieces
        box[0 * 9 + 2 * 3 + 1]->setColors(box[1 * 9 + 2 * 3 + 0]->getColors(), false, true);
        box[1 * 9 + 2 * 3 + 0]->setColors(box[2 * 9 + 2 * 3 + 1]->getColors(), false, true);
        box[2 * 9 + 2 * 3 + 1]->setColors(box[1 * 9 + 2 * 3 + 2]->getColors(), false, true);
        box[1 * 9 + 2 * 3 + 2]->setColors(tmp, false, true);
    }
}

void rotateLeftSide(bool reverted = false) {
    if(!reverted) {
        uint32_t* tmp = box[0 * 9 + 0 * 3]->getColors(); // Rotate corners
        box[0 * 9 + 0 * 3]->setColors(box[2 * 9 + 0 * 3]->getColors(), true);
        box[2 * 9 + 0 * 3]->setColors(box[2 * 9 + 2 * 3]->getColors(), true);
        box[2 * 9 + 2 * 3]->setColors(box[0 * 9 + 2 * 3]->getColors(), true);
        box[0 * 9 + 2 * 3]->setColors(tmp, true);
        
        tmp = box[1 * 9 + 0 * 3]->getColors(); // Rotate center pieces
        box[1 * 9 + 0 * 3]->setColors(box[2 * 9 + 1 * 3]->getColors(), true);
        box[2 * 9 + 1 * 3]->setColors(box[1 * 9 + 2 * 3]->getColors(), true);
        box[1 * 9 + 2 * 3]->setColors(box[0 * 9 + 1 * 3]->getColors(), true);
        box[0 * 9 + 1 * 3]->setColors(tmp, true);
    } else {
        uint32_t* tmp = box[0 * 9 + 0 * 3]->getColors(); // Rotate corners
        box[0 * 9 + 0 * 3]->setColors(box[0 * 9 + 2 * 3]->getColors(), true);
        box[0 * 9 + 2 * 3]->setColors(box[2 * 9 + 2 * 3]->getColors(), true);
        box[2 * 9 + 2 * 3]->setColors(box[2 * 9 + 0 * 3]->getColors(), true);
        box[2 * 9 + 0 * 3]->setColors(tmp, true);
        
        tmp = box[1 * 9 + 0 * 3]->getColors(); // Rotate center pieces
        box[1 * 9 + 0 * 3]->setColors(box[0 * 9 + 1 * 3]->getColors(), true);
        box[0 * 9 + 1 * 3]->setColors(box[1 * 9 + 2 * 3]->getColors(), true);
        box[1 * 9 + 2 * 3]->setColors(box[2 * 9 + 1 * 3]->getColors(), true);
        box[2 * 9 + 1 * 3]->setColors(tmp, true);
    }
}

void rotateTopSide(bool reverted = false) {
    if(reverted) {
        uint32_t* tmp = box[0 * 9 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 2]->setColors(box[0 * 9 + 0]->getColors(), false, true);
        box[0 * 9 + 0]->setColors(box[2 * 9 + 0]->getColors(), false, true);
        box[2 * 9 + 0]->setColors(box[2 * 9 + 2]->getColors(), false, true);
        box[2 * 9 + 2]->setColors(tmp, false, true);
        
        tmp = box[0 * 9 + 1]->getColors(); // Rotate center pieces
        box[0 * 9 + 1]->setColors(box[1 * 9 + 0]->getColors(), false, true);
        box[1 * 9 + 0]->setColors(box[2 * 9 + 1]->getColors(), false, true);
        box[2 * 9 + 1]->setColors(box[1 * 9 + 2]->getColors(), false, true);
        box[1 * 9 + 2]->setColors(tmp, false, true);
    } else {
        uint32_t* tmp = box[0 * 9 + 2]->getColors(); // Rotate corners
        box[0 * 9 + 2]->setColors(box[2 * 9 + 2]->getColors(), false, true);
        box[2 * 9 + 2]->setColors(box[2 * 9 + 0]->getColors(), false, true);
        box[2 * 9 + 0]->setColors(box[0 * 9 + 0]->getColors(), false, true);
        box[0 * 9 + 0]->setColors(tmp, false, true);
        
        tmp = box[0 * 9 + 1]->getColors(); // Rotate center pieces
        box[0 * 9 + 1]->setColors(box[1 * 9 + 2]->getColors(), false, true);
        box[1 * 9 + 2]->setColors(box[2 * 9 + 1]->getColors(), false, true);
        box[2 * 9 + 1]->setColors(box[1 * 9 + 0]->getColors(), false, true);
        box[1 * 9 + 0]->setColors(tmp, false, true);
    }
}

void test::cube::render() {
    shader->bind();
    angle += 0.005f;
    shader->uniformf("angle", angle); // For the whole shader
    
    for(int i = 0; i < 27; i++) box[i]->render(shader);
    
    if(keys[SDL_SCANCODE_RIGHT]) {
        if(!fetched[SDL_SCANCODE_RIGHT]) {
            rotateRightSide(keys[SDL_SCANCODE_LSHIFT]);
        }
        fetched[SDL_SCANCODE_RIGHT] = true;
    } else fetched[SDL_SCANCODE_RIGHT] = false;
    
    if(keys[SDL_SCANCODE_LEFT]) {
        if(!fetched[SDL_SCANCODE_LEFT]) {
            rotateLeftSide(keys[SDL_SCANCODE_LSHIFT]);
        }
        fetched[SDL_SCANCODE_LEFT] = true;
    } else fetched[SDL_SCANCODE_LEFT] = false;
    
    if(keys[SDL_SCANCODE_DOWN]) {
        if(!fetched[SDL_SCANCODE_DOWN]) {
            rotateBottomSide(keys[SDL_SCANCODE_LSHIFT]);
        }
        fetched[SDL_SCANCODE_DOWN] = true;
    } else fetched[SDL_SCANCODE_DOWN] = false;
    
    if(keys[SDL_SCANCODE_UP]) {
        if(!fetched[SDL_SCANCODE_UP]) {
            rotateTopSide(keys[SDL_SCANCODE_LSHIFT]);
        }
        fetched[SDL_SCANCODE_UP] = true;
    } else fetched[SDL_SCANCODE_UP] = false;
}
