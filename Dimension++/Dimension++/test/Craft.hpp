//
//  Craft.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Craft_hpp
#define Craft_hpp

#include "../graphics/Renderer.hpp"
#include "../graphics/Window.hpp"
#include "../util/Perlin.hpp"
#include "../util/Random.hpp"

namespace test {
    namespace craft {
        extern void init(graphics::Window *window);
        extern void render();
    }
}

#endif /* Craft_hpp */
