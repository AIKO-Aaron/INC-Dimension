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
		Matrix(Vector<M> v);
        
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

		Matrix<N, M> transpose();
		double det();
		Matrix<M, N> inv();
        
        inline Vector<N> getRow(int row) { return Vector<N>(&values[N * row]); }
        inline Vector<M> getColumn(int column) { double *d = new double[M]; for(int i = 0; i < M; i++) d[i] = values[N * i + column]; return Vector<M>(d); }

        template <int T>
        Matrix<M, T> operator*(Matrix<N, T> other);

		Matrix<M, N> operator*(double scalar);
		Matrix<M, N> operator*=(double scalar);
		Matrix<M, N> operator/(double scalar);
		Matrix<M, N> operator/=(double scalar);
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
maths::Matrix<M, N>::Matrix(Vector<M> v) {
	for (int i = 0; i < M * N; i++) values[i] = v[i / N];
}

template <int M, int N>
template <int T>
inline maths::Matrix<M, T> maths::Matrix<M, N>::operator*(Matrix<N, T> other) {
    maths::Matrix<M, T> result;
    for(int i = 0; i < M * T; i++) for(int j = 0; j < N; j++) result.values[i] += other.values[i % T + j * T] * values[(i / T) * N + j];
    return result;
}

template <int M, int N>
maths::Matrix<M, N> maths::Matrix<M, N>::operator*(double scalar) {
	Matrix<M, N> cpy = maths::Matrix<M, N>(values);
	for (int i = 0; i < M * N; i++) cpy.values[i] *= scalar;
	return cpy;
}

template <int M, int N>
maths::Matrix<M, N> maths::Matrix<M, N>::operator*=(double scalar) {
	for (int i = 0; i < M * N; i++) values[i] *= scalar;
	return *this;
}

template <int M, int N>
maths::Matrix<M, N> maths::Matrix<M, N>::operator/(double scalar) {
	Matrix<M, N> cpy = maths::Matrix<M, N>(values);
	for (int i = 0; i < M * N; i++) cpy.values[i] /= scalar;
	return cpy;
}

template <int M, int N>
maths::Matrix<M, N> maths::Matrix<M, N>::operator/=(double scalar) {
	for (int i = 0; i < M * N; i++) values[i] /= scalar;
	return *this;
}

template <int M, int N>
inline maths::Matrix<N, M> maths::Matrix<M, N>::transpose() {
	Matrix<N, M> n = Matrix<N, M>();
	for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) n.values[i + j * M] = values[i * N + j];
	return n;
}

template <int M, int N>
inline double maths::Matrix<M, N>::det() { // Calculate the determinant recursive until we have a 2 by 2 sub-matrix
	if (M != N) {
		printf("[ERROR] Trying to calculate determinant of no square matrix!\n");
		return 0;
	}

	bool negative = false;
	double det = 0;
	for (int i = 0; i < M; i++) {
		double *v = new double[(M - 1) * (M - 1)];
		int index = 0;
		for (int j = 0; j < M; j++) {
			if (j == i) continue;
			for (int k = 0; k < M - 1; k++) {
				v[index++] = values[(k + 1) * M + j];
			}
		}
		Matrix<M - 1, M - 1> sub = Matrix<M - 1, M - 1>(v);
		delete[] v;

		double x = values[i] * sub.det();
		if (negative) det -= x;
		else det += x;
		negative = !negative;
	}
	return det;
}

template <>
inline double maths::Matrix<2, 2>::det() { // "Exit-Condition" for the recursive determinant calculation
	return values[0] * values[3] - values[1] * values[2];
}

template <>
inline double maths::Matrix<1, 1>::det() { // Security, Don't want to crash (or not compile) without any error
	return values[0];
}

template <int M, int N>
inline maths::Matrix<M, N> maths::Matrix<M, N>::inv() {
	if (M != N) {
		printf("[ERROR] Trying to get inverse of not square matrix!\n");
		return *this;
	}

	Matrix<M, M> minors = Matrix<M, M>();
	double *v = new double[(M - 1) * (M - 1)]; // Create sub-matrix values
	bool negative = false;
	for (int i = 0; i < M * M; i++) {
		int index = 0;
		for (int j = 0; j < M; j++) {
			if (j == (i % M)) continue;
			for (int k = 0; k < M; k++) {
				if (k == (int)(i / M)) continue;
				v[index++] = values[k * M + j];
			}
		}
		Matrix<M - 1, M - 1> sub = Matrix<M - 1, M - 1>(v);
		minors.values[i] = sub.det() * (negative ? -1 : 1);
		negative = !negative;
	}
	delete[] v;

	double det = 0;
	for (int i = 0; i < M; i++) det += minors.values[i] * values[i];
	minors = minors.transpose();

	return minors / det;
}

// Util functions to create often used matrices

namespace maths {
    template <int D>
    static maths::Matrix<D, D> diagonal(double diagonal) {
        maths::Matrix<D, D> m;
        for(int i = 0; i < D; i++) m(i, i) = diagonal;
        return m;
    }
    
    static maths::Matrix<2, 2> rotate2(double angle) {
        return Matrix<2, 2>(new double[4] { cos(angle), -sin(angle), sin(angle), cos(angle) });
    }

	static maths::Matrix<3, 3> rotate3_z(double angle) {
		return Matrix<3, 3>(new double[9]{ 
			cos(angle), -sin(angle), 0,
			sin(angle), cos(angle), 0,
			0, 0, 1
		});
	}

	static maths::Matrix<3, 3> rotate3_y(double angle) {
		return Matrix<3, 3>(new double[9]{
			cos(angle), 0, sin(angle),
			0, 1, 0,
			-sin(angle), 0, cos(angle)
		});
	}

	static maths::Matrix<3, 3> rotate3_x(double angle) {
		return Matrix<3, 3>(new double[9]{
			1, 0, 0,
			0, cos(angle), -sin(angle),
			0, sin(angle), cos(angle)
		});
	}

	static maths::Matrix<4, 4> gl_4d(Matrix<3, 3> d) { // Convert 3d Matrix to 4d by adding 0s & 1s
		return Matrix<4, 4>(new double[16] {
			d(0, 0), d(0, 1), d(0, 2), 0,
			d(1, 0), d(1, 1), d(1, 2), 0,
			d(2, 0), d(2, 1), d(2, 2), 0,
			0, 0, 0, 1 });
	}

    static maths::Matrix<4, 4> translate3(double x, double y, double z) { // Create a translation matrix. Can't be 3 by 3, as those could only rotate & scale 3d space
        return Matrix<4, 4>(new double[16] {
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1 });
    }
}

#endif /* Matrix_hpp */
