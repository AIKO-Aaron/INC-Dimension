//
//  FileReader.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "FileReader.hpp"

using namespace util;

fileData util::readFile(const char *path) {
    FILE *f;
    fileData data = {0, nullptr};
    
#ifdef __APPLE__
    f = fopen(path, "rb");
#else
    fopen_s(&f, path, "rb");
#endif
    
    if(!f) {
        printf("[ERROR] File not found: \"%s\"\n", path);
        return data;
    }
    
    fseek(f, 0, SEEK_END);
    data.fileSize = ftell(f);
    data.fileContent = (uint8_t*) malloc(data.fileSize + 1);
    data.fileContent[data.fileSize] = 0;
    fseek(f, 0, SEEK_SET);
    
    fread(data.fileContent, sizeof(uint8_t), data.fileSize, f);
    
    fclose(f);
    
    return data;
}
