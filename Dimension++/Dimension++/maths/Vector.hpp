//
//  Vector.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

namespace maths {
    
    template<int D>
    class Vector {
    private:
        double *values = new double[D];
        
    public:
        Vector();
        Vector(double v);
        Vector(double *v);
        
        inline double &operator[](int index) { return values[index]; }
        
        double dot(Vector<D> other);
        inline double operator *(Vector<D> other) { return dot(other); }
        
        inline Vector<D> operator +(Vector<D> other) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] + other[i]; return result; }
        inline Vector<D> operator -(Vector<D> other) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] - other[i]; return result; }
        inline Vector<D> operator +=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] += other[i]; return *this; }
        inline Vector<D> operator -=(Vector<D> other) { for(int i = 0; i < D; i++) values[i] -= other[i]; return *this; }

        inline Vector<D> operator *(double scalar) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] * scalar; return result; }
        inline Vector<D> operator /(double scalar) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] / scalar; return result; }
        inline Vector<D> operator *=(double scalar) { for(int i = 0; i < D; i++) values[i] *= scalar; return *this; }
        inline Vector<D> operator /=(double scalar) { for(int i = 0; i < D; i++) values[i] /= scalar; return *this; }

        inline Vector<D> operator +(double vec) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] + vec; return result; }
        inline Vector<D> operator -(double vec) { Vector<D> result(0); for(int i = 0; i < D; i++) result[i] = values[i] - vec; return result; }
        inline Vector<D> operator +=(double vec) { for(int i = 0; i < D; i++) values[i] += vec; return *this; }
        inline Vector<D> operator -=(double vec) { for(int i = 0; i < D; i++) values[i] -= vec; return *this; }
    };
}

template <int D>
maths::Vector<D>::Vector() {
    for(int i = 0; i < D; i++) values[i] = 0;
}

template <int D>
maths::Vector<D>::Vector(double v) {
    for(int i = 0; i < D; i++) values[i] = v;
}

template <int D>
maths::Vector<D>::Vector(double *v) {
    for(int i = 0; i < D; i++) values[i] = v[i];
}

template <int D>
double maths::Vector<D>::dot(Vector<D> other) {
    double result = 0.0;
    for(int i = 0; i < D; i++) result += other[i] * values[i];
    return result;
}


#endif /* Vector_hpp */
