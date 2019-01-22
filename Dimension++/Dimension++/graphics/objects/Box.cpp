//
//  Box.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Box.hpp"

graphics::Box::Box() {
    glCreateBuffers(1, &vboID);
}
