//
//  Window.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"
#include "objects/Box.hpp"
#include "Shader.hpp"

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
    
    // Multisampling
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
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
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
    
    // glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

graphics::Window::Window(gameRender func) : renderFunc(func) {
    SDL_Init(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL | SDL_INIT_TIMER);
    setupGL(); // set up the gl context
    window = SDL_CreateWindow("3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    createContext(); // finally create the context
    renderer = new graphics::Renderer();
}

uint32_t graphics::second_callback(uint32_t, void *params) {
    graphics::Window *window = (graphics::Window*) params;
    if(!window || !window->window) return 1000;
    window->lastFPS = window->fps;
    window->updateTitle = true;
    window->fps = 0;
    return 1000;
}

void graphics::Window::run() {
    running = true;
    SDL_Event e;
    
    SDL_AddTimer(1000, second_callback, this);
    std::chrono::high_resolution_clock clock = std::chrono::high_resolution_clock(); // Create high accuracy clock
    auto start_time = clock.now(); // Now --> used to wait afterwards
    
    while(running) {
        start_time = clock.now();
        while(SDL_PollEvent(&e)) {
            for(gameEvent handler : eventHandlers) {
                handler(e);
            }
            
            if(e.type == SDL_WINDOWEVENT) {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
                else if(e.window.event == SDL_WINDOWEVENT_RESIZED) glViewport(0, 0, e.window.data1, e.window.data2);
            } else if(e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
            } else if(e.type == SDL_QUIT) {
                running = false;
            }
        }
        
        if(updateTitle) {
            SDL_SetWindowTitle(window, (std::string("3D | ") + std::to_string(lastFPS) + std::string(" FPS")).c_str());
            updateTitle = false;
        }
        
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        renderFunc();
        
        // If there was an error print it
        GLenum err = glGetError();
        if(err != GL_NO_ERROR) {
            printf("[ERROR] GL Error: %d\n", err);
        }
        
        SDL_GL_SwapWindow(window);
        
        ++fps;
        auto end_time = clock.now();
        auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        if(difference.count() > 0) std::this_thread::sleep_for(std::chrono::microseconds(1000000 / 60 - 588) - difference);
    }
}

graphics::Window::~Window() {
    delete renderer;
    SDL_DestroyWindow(window);
}
