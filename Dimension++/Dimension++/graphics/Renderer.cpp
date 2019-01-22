//
//  Renderer.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Renderer.hpp"

graphics::Renderer::Renderer() {
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

graphics::Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vaoID);
}
