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

static util::fileData loadShaderRecursive(const char *filePath, int depth = 9) {
    if(!depth) return util::readFile(filePath); // Don't load more than 10 files recursively, exit condition
    
    util::fileData fd = util::readFile(filePath);
    
    printf("[INFO] Loading shader: %s\n", filePath);
    
    int s = 0;
    while(s < fd.fileSize) {
        if(fd.fileContent[s++] == '\n') { // newline char
            while(fd.fileContent[s] == ' ' || fd.fileContent[s] == '\t') ++s;
            if(fd.fileContent[s] == '#') { // We're in a preprocessor statement
                int len = 0; // Length of directive
                int start = s; // Start at current offset in file
                while(fd.fileContent[s++] != '\n') ++len; // Search for next newline
                
                // Load the preprocessor directive into str
                char *str = (char*) malloc(len + 1);
                memcpy(str, fd.fileContent + start, len);
                str[len] = 0;
                
                // Check if is a not known directive (Filesystem, ...)
                if(!memcmp(str, "#include ", 9)) {
                    int i = 9;
                    while(str[i++] != '"') ; // Search for beginning of string
                    int j = i + 1;
                    while(str[j++] != '"') ; // Search for end of string
                    
                    char *filename = (char*) malloc(j - i);
                    memcpy(filename, str + i, j - i);
                    filename[j - i - 1] = 0;
                    
                    util::fileData loadedFile = loadShaderRecursive(filename, depth - 1);
                    
                    // data + start until j+1
                    uint64_t newFileSize = fd.fileSize - s + start + loadedFile.fileSize;
                    char *newFile = (char*) malloc(newFileSize + 1);
                    memcpy(newFile, fd.fileContent, start);
                    memcpy(newFile + start, loadedFile.fileContent, loadedFile.fileSize);
                    memcpy(newFile + start + loadedFile.fileSize, fd.fileContent + start + j + 1, fd.fileSize - s);
                    newFile[newFileSize] = 0;
                    
                    free(loadedFile.fileContent); // Free newly loaded file
                    free(filename); // Free the filename string
                    free(fd.fileContent); // Free the fileContents of the file, as we have a new one
                    fd.fileContent = (uint8_t*) newFile; // Set the pointer in fd to the new one
                    fd.fileSize = newFileSize; // Update the size
                    
                    //printf("%s", fd.fileContent);
                    s = start - 1; // Go back to the start of the line
                }
                
                free(str);
            }
        }
    }
    
    return fd;
}

graphics::Shader *graphics::loadFromFiles(const char *vertPath, const char *fragPath) {
    return new Shader((const char*) loadShaderRecursive(vertPath).fileContent, (const char*) loadShaderRecursive(fragPath).fileContent);
}
