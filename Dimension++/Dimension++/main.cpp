//
//  main.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

// #define _CUBE
#define _CRAFT
// #define _WAVE

#if defined(_CUBE)
#  include "test/Cube.hpp"
#  define TEST_GAME cube
#elif defined(_CRAFT)
#  include "test/Craft.hpp"
#  define TEST_GAME craft
#elif defined(_WAVE)
#  include "test/Wave.hpp"
#  define TEST_GAME wave
#endif

#include "graphics/Window.hpp"
#include "maths/Vector.hpp"
#include "maths/Matrix.hpp"

int main(int argc, const char * argv[]) {
    graphics::Window *window = new graphics::Window(test::TEST_GAME::render);
    test::TEST_GAME::init(window);
    window->run();
    
    maths::Matrix<4, 1> pos = maths::Matrix<4, 1>(new double[4] { 1, 2, 3, 1 });
    maths::Matrix<4, 4> translation = maths::translate3(1, 2, 3);
    (translation * pos).print();

    return 0;
}
