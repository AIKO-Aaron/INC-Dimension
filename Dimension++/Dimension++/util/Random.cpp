//
//  Random.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Random.hpp"

util::Random::Random() {
    startSeed = (uint32_t) time(NULL);
    reset();
}

util::Random::Random(uint32_t seed) {
    startSeed = seed;
    reset();
}

uint32_t util::Random::randomInt(int max) {
    return rand() % max;
}

uint32_t util::Random::randomInt(int min, int max) {
    return (rand() % (max-min)) + min;
}

float util::Random::randomFloat() {
    return (float) rand() / (float) RAND_MAX;
}

