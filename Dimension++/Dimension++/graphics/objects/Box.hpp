//
//  Box.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#ifdef __APPLE__
#  include <GL/glew.h>
#else
#  include "../glew/GL/glew.h"
#endif

#include <stdio.h>

namespace graphics {
    static const uint8_t *indicies = new uint8_t[36] {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        0, 4, 5,
        5, 1, 0,
        
        2, 3, 7,
        7, 6, 2,
        
        0, 3, 7,
        7, 4, 0,
        
        1, 2, 6,
        6, 5, 1
    };
    
    class Box {
    private:
        GLuint vboID = 0, iboID = 0, vaoID = 0;
        
    public:
        Box(float x, float y, float z, float w, float h, float d);
        void render();
    };
}

#endif /* Box_hpp */
