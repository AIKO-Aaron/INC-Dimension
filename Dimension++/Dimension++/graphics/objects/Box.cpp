//
//  Box.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Box.hpp"

graphics::Box::Box(float x, float y, float z, float w, float h, float d) {
    glGenBuffers(1, &vboID); // The verticies (points)
    glGenBuffers(1, &iboID); // The indicies (When which point)
    
    GLfloat *verticies = new GLfloat[2 * 8 * 3] {
        x + 0, y + 0, z + 0,
        1, 0, 0,
        x + w, y + 0, z + 0,
        0, 1, 0,
        x + w, y + h, z + 0,
        0, 0, 1,
        x + 0, y + h, z + 0,
        1, 1, 0,
        x + 0, y + 0, z + d,
        1, 0, 0,
        x + w, y + 0, z + d,
        1, 0, 0,
        x + w, y + h, z + d,
        1, 1, 1,
        x + 0, y + h, z + d,
        1, 0, 1,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 24, verticies, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36, indicies, GL_STATIC_DRAW);
}

void graphics::Box::render() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
