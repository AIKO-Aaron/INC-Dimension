//
//  Window.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window() {
    window = SDL_CreateWindow("3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_ShowWindow(window);
    
    bool running = true;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            }
        }
    }
    
    SDL_DestroyWindow(window);
}
