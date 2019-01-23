//
//  main.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "test/Cube.hpp"
#include "graphics/Window.hpp"

int main(int argc, const char * argv[]) {
    graphics::Window *window = new graphics::Window(test::cube::render);
    test::cube::init();
    window->run();
    return 0;
}
