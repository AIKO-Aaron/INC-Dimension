//
//  Wave.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Wave_hpp
#define Wave_hpp

#include "../graphics/Renderer.hpp"
#include "../graphics/Window.hpp"
#include "../util/Perlin.hpp"
#include "../util/Random.hpp"

namespace test {
    namespace wave {
        extern void init(graphics::Window *window);
        extern void render();
    }
}

#endif /* Wave_hpp */
