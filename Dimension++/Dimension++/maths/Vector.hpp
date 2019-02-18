//
//  Vector.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <cmath>
#include <stdio.h>

namespace maths {
    
    template<int D>
    class Vector {
    private:
        float *values = new float[D];
        
    public:
        Vector();
        Vector(float v);
        Vector(float *v);
        
        inline float &operator[](int index) { return values[index]; }
        
        float dot(Vector<D> other);
        inline float operator *(Vector<D> other) { return dot(other); }
        
        inline Vector<D> operator +(Vector<D> other) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] + other[i]; return result; }
        inline Vector<D> operator -(Vector<D> other) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] - other[i]; return result; }
        inline Vector<D> operator +=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] += other[i]; return *this; }
        inline Vector<D> operator -=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] -= other[i]; return *this; }

        inline Vector<D> operator *(float scalar) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] * scalar; return result; }
        inline Vector<D> operator /(float scalar) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] / scalar; return result; }
        inline Vector<D> operator *=(float scalar) { for(int i = 0; i < D; i++) values[i] *= scalar; return *this; }
        inline Vector<D> operator /=(float scalar) { for(int i = 0; i < D; i++) values[i] /= scalar; return *this; }

        inline Vector<D> operator +(float vec) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] + vec; return result; }
        inline Vector<D> operator -(float vec) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] - vec; return result; }
        inline Vector<D> operator +=(float vec) { for(int i = 0; i < D; i++) values[i] += vec; return *this; }
        inline Vector<D> operator -=(float vec) { for(int i = 0; i < D; i++) values[i] -= vec; return *this; }
    };
}

template <int D>
maths::Vector<D>::Vector() {
    for(int i = 0; i < D; i++) values[i] = 0;
}

template <int D>
maths::Vector<D>::Vector(float v) {
    for(int i = 0; i < D; i++) values[i] = v;
}

template <int D>
maths::Vector<D>::Vector(float *v) {
    for(int i = 0; i < D; i++) values[i] = v[i];
}

template <int D>
float maths::Vector<D>::dot(Vector<D> other) {
    float result = 0.0;
    for(int i = 0; i < D; i++) result += other[i] * values[i];
    return result;
}


#endif /* Vector_hpp */
