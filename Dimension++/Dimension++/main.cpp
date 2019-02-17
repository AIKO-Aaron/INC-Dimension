//
//  main.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 22.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

// #define _CUBE
//#define _CRAFT
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

int main(int argc, char **args) {
#ifdef TEST_GAME
    graphics::Window *window = new graphics::Window(test::TEST_GAME::render);
    test::TEST_GAME::init(window);
    window->run();
#endif

	maths::Vector<3> v = maths::Vector<3>(new double[3]{ 1, 2, 3 });
	maths::Matrix<3, 3> m = maths::Matrix<3, 3>(v);
	m.print();
	maths::gl_4d(m).print();

    maths::Matrix<4, 1> pos = maths::Matrix<4, 1>(new double[4] { 1, 2, 3, 1 });
    maths::Matrix<4, 4> translation = maths::translate3(1, 2, 3);
    (translation * pos).print();

	maths::Matrix<4, 4> test_det = maths::Matrix<4, 4>(new double[16]{ 1, 3, 2, -6, 1, 2, -2, -5, 2, 4, -2, -9, 2, 4, -6, -9 });
	printf("Determinant of matrix: %f\n", test_det.det());

	maths::Matrix<3, 3> test_inv = maths::Matrix<3, 3>(new double[9]{3, 0, 2, 2, 0, -2, 0, 1, 1});
	(test_inv.inv() * test_inv).print();

    return 0;
}
