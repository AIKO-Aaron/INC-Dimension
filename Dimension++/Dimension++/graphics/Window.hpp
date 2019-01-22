//
//  Window.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <SDL2/SDL_opengl.h>
#  include <SDL2/SDL.h>
#else
#  include "../glew/GL/glew.h"
#  include <SDL.h>
#  include <SDL_opengl.h>
#endif

#include "../config/GameConfig.h"

class Window {
private:
    SDL_Window *window = nullptr;
    
public:
    Window();
};

#endif /* Window_hpp */
