//
//  Window.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

void graphics::Window::setupGL() {
    // Set up GL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Load GL version 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // .2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // The core profile (Macs don't have more than that above GL version 2.1)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Enable accelerated graphics
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering (No flickering)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Set the forward compability flag (Not sure if needed, but macs seem to need it)
    
    // 8 bits per color channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
}

void graphics::Window::createContext() {
    context = SDL_GL_CreateContext(window);
    if(context == nullptr) { // Check if we succeeded
        printf("[ERROR] Couldn't create GL context\n");
        exit(0);
    }
    
    // Initialize Glew to set up the function pointers to the gl functions
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("[ERROR] Error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_GL_SetSwapInterval(1); // Enable Vsync for OpenGL
}

graphics::Window::Window() {
    SDL_Init(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL | SDL_INIT_TIMER);
    setupGL(); // set up the gl context
    window = SDL_CreateWindow("3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    createContext(); // finally create the context
    renderer = new graphics::Renderer();
}

void graphics::Window::run() {
    running = true;
    SDL_Event e;
    
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            } else if(e.type == SDL_KEYDOWN) {
                
            } else if(e.type == SDL_QUIT) {
                running = false;
            }
        }
        
        glClearColor(1, 0, 1, 1);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
}

graphics::Window::~Window() {
    delete renderer;
    SDL_DestroyWindow(window);
}
