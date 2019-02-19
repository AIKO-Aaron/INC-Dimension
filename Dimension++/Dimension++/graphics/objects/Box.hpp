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

#include "../Texture.hpp"
#include "../Shader.hpp"
#include "../../maths/Matrix.hpp"

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
    
    static const uint8_t *textures_indicies = new uint8_t[36] {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,
        
        16, 17, 18,
        18, 19, 16,
        
        20, 21, 22,
        22, 23, 20
    };
    
    class Box {
    private:
        GLuint vboID = 0, iboID = 0, vaoID = 0;
        GLfloat *verticies = nullptr;
        maths::Matrix<4, 4> modelview = maths::diagonal<4>(1); // identity
        
        Texture *texture = nullptr;
        
    public:
        Box(float x, float y, float z, float w, float h, float d);
        Box(float x, float y, float z, float w, float h, float d, Texture *texture);
        
        Box(float x, float y, float z, float w, float h, float d, uint32_t tb, uint32_t lr, uint32_t fb);
        void setColors(uint32_t *colrs, bool rx = false, bool ry = false, bool rz = false);
        uint32_t *getColors();
        
        inline void resetModelView() { modelview = maths::diagonal<4>(1); }
        inline void applyTransformation(maths::Matrix<4, 4> transformation) { modelview = modelview * transformation; }
        inline maths::Matrix<4, 4> getTransformation() { return modelview; }
        
        void render(Shader *shader);
    };
}

#endif /* Box_hpp */
