//
//  Random.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include <stdint.h>
#include <random>
#include <time.h>

namespace util {
    class Random {
    private:
        uint32_t startSeed;
        
    public:
        Random();
        Random(uint32_t seed);
        
        inline void reset() { srand(startSeed); }
        
        uint32_t randomInt(int max);
        uint32_t randomInt(int min, int max);
        float randomFloat();
    };
}

#endif /* Random_hpp */
