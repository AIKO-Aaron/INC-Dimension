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

namespace graphics {
    class Box {
    private:
        GLuint vboID;
        
    public:
        Box();
    };
}

#endif /* Box_hpp */
