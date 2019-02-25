//
//  Box.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Box.hpp"

#define RED_PART(x) ((float) (((x) >> 16) & 0xFF) / 255.0f)
#define GREEN_PART(x) ((float) (((x) >> 8) & 0xFF) / 255.0f)
#define BLUE_PART(x) ((float) ((x) & 0xFF) / 255.0f)

graphics::Box::Box(float x, float y, float z, float w, float h, float d) {
    glGenBuffers(1, &vboID); // The verticies (points)
    glGenBuffers(1, &iboID); // The indicies (When which point)
    glGenVertexArrays(1, &vaoID);
    
    verticies = new GLfloat[2 * 8 * 3] {
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
    
    glBindVertexArray(vaoID);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBindVertexArray(0);
}

graphics::Box::Box(float x, float y, float z, float w, float h, float d, Texture *tex) : texture(tex) {
    glGenBuffers(1, &vboID); // The verticies (points)
    glGenBuffers(1, &iboID); // The indicies (When which point)
    glGenVertexArrays(1, &vaoID);
    
    vertexAttribs *verts = new vertexAttribs[24];
    
    verts[0] = { x, y, z, 0, 0 };
    verts[1] = { x + w, y, z, 1, 0 };
    verts[2] = { x + w, y + h, z, 1, 1 };
    verts[3] = { x, y + h, z, 0, 1 };
    
    verts[4] = { x, y, z + d, 0, 0 };
    verts[5] = { x, y + h, z + d, 1, 0 };
    verts[6] = { x + w, y + h, z + d, 1, 1 };
    verts[7] = { x + w, y, z + d, 0, 1 };
    
    verts[8]  = { x, y, z, 0, 0 };
    verts[9]  = { x, y, z + d, 1, 0 };
    verts[10] = { x + w, y, z + d, 1, 1 };
    verts[11] = { x + w, y, z, 0, 1 };

    verts[12] = { x, y + h, z, 0, 0 };
    verts[13] = { x + w, y + h, z, 1, 0 };
    verts[14] = { x + w, y + h, z + d, 1, 1 };
    verts[15] = { x, y + h, z + d, 0, 1, };

    verts[16] = { x, y, z, 0, 0 };
    verts[17] = { x, y + h, z, 1, 0 };
    verts[18] = { x, y + h, z + d, 1, 1 };
    verts[19] = { x, y, z + d, 0, 1 };

    verts[20] = { x + w, y, z, 0, 0 };
    verts[21] = { x + w, y, z + d, 1, 0 };
    verts[22] = { x + w, y + h, z + d, 1, 1 };
    verts[23] = { x + w, y + h, z, 0, 1 };
    
    for(int i = 0; i < 24; i++) {
        maths::Vector<3> a = maths::Vector<3>((float*) &verts[(i / 4)]);
        maths::Vector<3> b = maths::Vector<3>((float*) &verts[(i / 4) + 1]);
        maths::Vector<3> c = maths::Vector<3>((float*) &verts[(i / 4) + 2]);
        
        maths::Vector<3> normal = maths::cross(b - a, c - a);
        verts[i].nx = normal[0];
        verts[i].ny = normal[1];
        verts[i].nz = normal[2];
    }

    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttribs) * 24, verts, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36, textures_indicies, GL_STATIC_DRAW);
    
    glBindVertexArray(vaoID);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertexAttribs), 0); // Screen coords
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertexAttribs), (void*) (3 * sizeof(GLfloat))); // UV-coords
    glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(vertexAttribs), (void*) (5 * sizeof(GLfloat))); // Normal vectors

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBindVertexArray(0);
}

graphics::Box::Box(float x, float y, float z, float w, float h, float d, uint32_t tb, uint32_t lr, uint32_t fb) {
    glGenBuffers(1, &vboID); // The verticies (points)
    glGenBuffers(1, &iboID); // The indicies (When which point)
    glGenVertexArrays(1, &vaoID);
    
    verticies = new GLfloat[6 * 24] {
        x + 0, y + 0, z + 0,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + w, y + 0, z + 0,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + w, y + h, z + 0,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + 0, y + h, z + 0,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),

        x + 0, y + 0, z + d,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + w, y + 0, z + d,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + w, y + h, z + d,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),
        x + 0, y + h, z + d,
        RED_PART(fb), GREEN_PART(fb), BLUE_PART(fb),

        x + 0, y + 0, z + 0,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + 0, y + 0, z + d,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + w, y + 0, z + d,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + w, y + 0, z + 0,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),

        x + 0, y + h, z + 0,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + 0, y + h, z + d,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + w, y + h, z + d,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),
        x + w, y + h, z + 0,
        RED_PART(tb), GREEN_PART(tb), BLUE_PART(tb),

        x + 0, y + 0, z + 0,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + 0, y + 0, z + d,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + 0, y + h, z + d,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + 0, y + h, z + 0,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),

        x + w, y + 0, z + 0,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + w, y + 0, z + d,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + w, y + h, z + d,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
        x + w, y + h, z + 0,
        RED_PART(lr), GREEN_PART(lr), BLUE_PART(lr),
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 24, verticies, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36, textures_indicies, GL_STATIC_DRAW);
    
    glBindVertexArray(vaoID);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), 0); // Screen coords
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBindVertexArray(0);
}

void graphics::Box::setColors(uint32_t *colors, bool rotateX, bool rotateY, bool rotateZ) {
    for(int i = 0; i < 8; i++) {
        // front & back colors
        verticies[6 * i + 3] = RED_PART(colors[rotateX ? 1 : rotateY ? 2 : 0]);
        verticies[6 * i + 4] = GREEN_PART(colors[rotateX ? 1 : rotateY ? 2 : 0]);
        verticies[6 * i + 5] = BLUE_PART(colors[rotateX ? 1 : rotateY ? 2 : 0]);
        
        // Top & Bottom colors
        verticies[6 * i + 51] = RED_PART(colors[rotateX ? 0 : rotateZ ? 2 : 1]);
        verticies[6 * i + 52] = GREEN_PART(colors[rotateX ? 0 : rotateZ ? 2 : 1]);
        verticies[6 * i + 53] = BLUE_PART(colors[rotateX ? 0 : rotateZ ? 2 : 1]);
        
        // Left & right colors
        verticies[6 * i + 99] = RED_PART(colors[rotateY ? 0 : rotateZ ? 1 : 2]);
        verticies[6 * i + 100] = GREEN_PART(colors[rotateY ? 0 : rotateZ ? 1 : 2]);
        verticies[6 * i + 101] = BLUE_PART(colors[rotateY ? 0 : rotateZ ? 1 : 2]);
    }
    
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 24, verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    
    delete[] colors;
}

uint32_t *graphics::Box::getColors() {
    uint32_t *cols = new uint32_t[3];
    
    cols[0] = (((int)(verticies[3] * 255.0f)) << 16) | (((int)(verticies[4] * 255.0f)) << 8) | (((int)(verticies[5] * 255.0f)));
    cols[1] = (((int)(verticies[51] * 255.0f)) << 16) | (((int)(verticies[52] * 255.0f)) << 8) | (((int)(verticies[53] * 255.0f)));
    cols[2] = (((int)(verticies[99] * 255.0f)) << 16) | (((int)(verticies[100] * 255.0f)) << 8) | (((int)(verticies[101] * 255.0f)));
    
    return cols;
}

void graphics::Box::render(graphics::Shader *shader) {
    glBindVertexArray(vaoID);
    if(texture) texture->bind(0);
    if(modelview != 1.0f) shader->uniformMatrix4("modelview", modelview);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
}
