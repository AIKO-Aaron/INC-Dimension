//
//  Matrix.hpp
//  Dimension++
//
//  Created by Aaron Hodel on 29.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vector.hpp"

namespace maths {
    
    template <int M, int N>
    class Matrix {
    public:
        double *values = new double[N * M];

    public:
        Matrix();
        Matrix(double filler);
        Matrix(double *values);
        
        inline void print() {
            printf("Matrix (%d|%d)\n[\n", M, N);
            for(int i = 0; i < M; i++) {
                for(int j = 0; j < N; j++) {
                    printf(j == N-1 ? "\t%f" : "\t%f, ", values[i * N + j]);
                }
                printf("\n");
            }
            printf("]\n");
        }
        
        inline double &operator()(int y, int x) { return values[y * N + x]; }
        inline double &operator[](int index) { return values[index]; }
        
        inline Vector<N> getRow(int row) { return Vector<N>(&values[N * row]); }
        inline Vector<M> getColumn(int column) { double *d = new double[M]; for(int i = 0; i < M; i++) d[i] = values[N * i + column]; return Vector<M>(d); }

        template <int T>
        Matrix<M, T> operator*(Matrix<N, T> other);
    };
}

template <int M, int N>
maths::Matrix<M, N>::Matrix() {
    for(int i = 0; i < M * N; i++) values[i] = 0;
}

template <int M, int N>
maths::Matrix<M, N>::Matrix(double filler) {
    for(int i = 0; i < M * N; i++) values[i] = filler;
}

template <int M, int N>
maths::Matrix<M, N>::Matrix(double *v) {
    for(int i = 0; i < M * N; i++) values[i] = v[i];
}

template <int M, int N>
template <int T>
maths::Matrix<M, T> maths::Matrix<M, N>::operator*(Matrix<N, T> other) {
    maths::Matrix<M, T> result;
    for(int i = 0; i < M * T; i++) for(int j = 0; j < N; j++) result.values[i] += other.values[i % T + j * T] * values[(i / T) * N + j];
    return result;
}

namespace maths {
    template <int D>
    static maths::Matrix<D, D> diagonal(double diagonal) {
        maths::Matrix<D, D> m;
        for(int i = 0; i < D; i++) m(i, i) = diagonal;
        // m.print();
        return m;
    }
    
    static maths::Matrix<2, 2> rotate2(double angle) {
        return Matrix<2, 2>(new double[4] { cos(angle), sin(angle), -sin(angle), cos(angle) });
    }
    
    static maths::Matrix<4, 4> translate3(double x, double y, double z) {
        return Matrix<4, 4>(new double[16] {
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1 });
    }
}

#endif /* Matrix_hpp */
