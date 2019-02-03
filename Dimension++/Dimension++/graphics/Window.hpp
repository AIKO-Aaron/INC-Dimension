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
#include <vector>

namespace graphics {
    typedef void (*gameRender)();
    typedef void (*gameEvent)(SDL_Event);
    
    class Window {
    private:
        // Graphics variables
        SDL_Window *window = nullptr;
        SDL_GLContext context;
        Renderer *renderer;
        gameRender renderFunc;
        std::vector<gameEvent> eventHandlers = std::vector<gameEvent>();
        
        // Util variables
        bool running;
        
        // Private functions (init, ...)
        void setupGL();
        void createContext();

    public:
        Window(gameRender func);
        ~Window();
        
        inline void addEventHandler(gameEvent func) { eventHandlers.push_back(func); }
        inline SDL_Window* getWindow() { return window; }
        
        void run();
    };
}

#endif /* Window_hpp */
