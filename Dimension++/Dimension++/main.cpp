//
//  main.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "graphics/Window.hpp"
#include "graphics/Shader.hpp"

int main(int argc, const char * argv[]) {
    graphics::Window *window = new graphics::Window();
    window->run();
    return 0;
}
