//
//  Renderer.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <SDL2/SDL_opengl.h>
#  include <SDL2/SDL.h>
#else
#  include "../glew/GL/glew.h"
#  include <SDL.h>
#  include <SDL_opengl.h>
#endif

#include "objects/Box.hpp"
#include "Shader.hpp"

namespace graphics {
    class Renderer {
    private:
        GLuint vaoID = 0;
        
    public:
        Renderer();
        ~Renderer();
    };
}

#endif /* Renderer_hpp */
