//
//  Perlin.cpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "Perlin.hpp"

util::Perlin::Perlin(uint32_t seed) {
    permutations = new int[512];
    for(int i = 0; i < 256; i++) permutations[i] = i; // Fill with all numbers to 255
    
    srand(seed);
    int tmp, l1, l2;
    for(int i = 0; i < 256 * 256; i++) { // Swap randomly selected values a total of 256*256 times, so every value could be swapped with every value
        l1 = rand() & 0xFF;
        l2 = rand() & 0xFF;
        tmp = permutations[l1];
        permutations[l1] = permutations[l2];
        permutations[l2] = tmp;
    }
    
    for(int i = 0; i < 256; i++) permutations[256 + i] = permutations[i]; // Double up
}

double util::Perlin::fade(double t) {
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double util::Perlin::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double util::Perlin::gradient(int hash, double x, double y, double z) {
    int h = hash & 0xF;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double util::Perlin::noise(double x, double y, double z) {
    int X = (int) floor(x) & 0xFF;
    int Y = (int) floor(y) & 0xFF;
    int Z = (int) floor(z) & 0xFF;
    
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    
    int A = permutations[X] + Y;
    int AA = permutations[A] + Z;
    int AB = permutations[A + 1] + Z;
    
    int B = permutations[X + 1] + Y;
    int BA = permutations[B] + Z;
    int BB = permutations[B + 1] + Z;

    double g1 = gradient(permutations[AA], x, y, z);
    double g2 = gradient(permutations[BA], x - 1, y, z);
    double g3 = gradient(permutations[AB], x, y - 1, z);
    double g4 = gradient(permutations[BB], x - 1, y - 1, z);
    double g5 = gradient(permutations[AA+1], x, y, z - 1);
    double g6 = gradient(permutations[BA+1], x - 1, y, z - 1);
    double g7 = gradient(permutations[AB+1], x, y - 1, z - 1);
    double g8 = gradient(permutations[BB+1], x - 1, y - 1, z - 1);

    
    double x1 = lerp(u, g1, g2);
    double x2 = lerp(u, g3, g4);
    double x3 = lerp(u, g5, g6);
    double x4 = lerp(u, g7, g8);
    
    double y1 = lerp(v, x1, x2);
    double y2 = lerp(v, x3, x4);
    
    return lerp(w, y1, y2);
}
