//
//  Perlin.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Perlin_hpp
#define Perlin_hpp

#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <random>

namespace util {
    class Perlin {
    private:
        int *permutations;
        
        double fade(double time);
        double lerp(double time, double a, double b);
        double gradient(int hash, double x, double y, double z);
        
    public:
        
        Perlin(uint32_t seed);
        double noise(double x, double y, double z);
    };
}

#endif /* Perlin_hpp */
