//
//  Shader.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Shader.hpp"
#include "../util/FileReader.hpp"

graphics::Shader::Shader(const char *vertSrc, const char *fragSrc) {
    GLuint vid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vid, 1, &vertSrc, nullptr);
    glCompileShader(vid);
    
    GLint status;
    glGetShaderiv(vid, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        printf("[ERROR] Couldn't compile vertex shader:\n%s\n", vertSrc);
        glGetShaderiv(vid, GL_INFO_LOG_LENGTH, &status);
        char* errorlog = (char*) malloc(status + 1);
        glGetShaderInfoLog(vid, status, &status, errorlog);
        printf("%s\n", errorlog);
        free(errorlog);
    }
    
    GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fid, 1, &fragSrc, nullptr);
    glCompileShader(fid);
    
    glGetShaderiv(fid, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        printf("[ERROR] Couldn't compile fragment shader:\n%s\n", fragSrc);
        glGetShaderiv(fid, GL_INFO_LOG_LENGTH, &status);
        char* errorlog = (char*) malloc(status + 1);
        glGetShaderInfoLog(fid, status, &status, errorlog);
        printf("%s\n", errorlog);
        free(errorlog);
    }
    
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vid);
    glAttachShader(shaderID, fid);
    glLinkProgram(shaderID);
    glDeleteShader(vid);
    glDeleteShader(fid);
    
    glGetProgramiv(shaderID, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        printf("[ERROR] Couldn't link shader:\n");
        glGetProgramiv(fid, GL_INFO_LOG_LENGTH, &status);
        char* errorlog = (char*) malloc(status + 1);
        glGetProgramInfoLog(shaderID, status, &status, errorlog);
        printf("%s\n", errorlog);
        free(errorlog);
    }
}

graphics::Shader *graphics::loadFromFiles(const char *vertPath, const char *fragPath) {
    return new Shader((const char*) readFile(vertPath).fileContent, (const char*) readFile(fragPath).fileContent);
}
