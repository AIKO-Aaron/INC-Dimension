//
//  FileReader.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <string>
#include <stdio.h>
#include <stdint.h>

typedef struct fileData {
    uint64_t fileSize;
    uint8_t *fileContent;
} fileData;

extern fileData readFile(const char *path);

#endif /* FileReader_hpp */
