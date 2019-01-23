//
//  Texture.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 23.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

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

namespace graphics {
    
    class Texture {
    private:
        GLuint texID = 0;
        
    public:
        Texture(const char* path);
        inline void bind(int location) { glActiveTexture(GL_TEXTURE0 + location); glBindTexture(GL_TEXTURE_2D, texID); } // unbind necessary, just don't use unused textures...
    };
    
}

#endif /* Texture_hpp */
