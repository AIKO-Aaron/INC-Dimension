//
//  Window.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "../config/GameConfig.h"
#include "Renderer.hpp"
#include <chrono>
#include <thread>

namespace graphics {
    typedef void (*gameRender)();
    
    class Window {
    private:
        // Graphics variables
        SDL_Window *window = nullptr;
        SDL_GLContext context;
        Renderer *renderer;
        gameRender renderFunc;
        
        // Util variables
        bool running;
        
        // Private functions (init, ...)
        void setupGL();
        void createContext();
        
    public:
        Window(gameRender func);
        ~Window();
        
        void run();
    };
}

#endif /* Window_hpp */
