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
#  include <SDL2_image/SDL_image.h>
#else
#  include "../glew/GL/glew.h"
#  include <SDL.h>
#  include <SDL_opengl.h>
#  include <SDL_image.h>
#endif

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

#include "objects/Box.hpp" // Just need the definition, so we don't need to include box (or whatever else) extra
#include "Texture.hpp"

#endif /* Renderer_hpp */
