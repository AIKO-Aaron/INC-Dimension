//
//  Shader.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#ifdef __APPLE__
#  include <GL/glew.h>
#else
#  include "../glew/GL/glew.h"
#endif

namespace graphics {
    class Shader {
    private:
        GLuint shaderID = 0;
        
    public:
        Shader(const char *vertSrc, const char *fragSrc);
        ~Shader();
        
        inline void bind() { glUseProgram(shaderID); }
        inline void unbind() { glUseProgram(0); }
        
        inline void uniformf(const char* name, float value) { glUniform1f(glGetUniformLocation(shaderID, name), value); }
        inline void uniformi(const char* name, int value) { glUniform1i(glGetUniformLocation(shaderID, name), value); }
    };
    
    extern Shader *loadFromFiles(const char *vertPath, const char* fragPath);
}

#endif /* Shader_hpp */
