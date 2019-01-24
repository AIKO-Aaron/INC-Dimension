//
//  Texture.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 23.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Texture.hpp"

graphics::Texture::Texture(const char *path) {
    glGenTextures(1, &texID); // Create the texture
    
    glBindTexture(GL_TEXTURE_2D, texID);
    
    // Set settings for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    SDL_Surface *surface = IMG_Load(path);
    SDL_Surface *converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, surface->flags);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, converted->pixels);
}
