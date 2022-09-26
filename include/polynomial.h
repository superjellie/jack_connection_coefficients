#pragma once

#include <big_int.h>

// *** Methods for polynomial arithmetics ***

// multiply by variable: polynomial(x) = x * polynomial(x)
void shift_right_big_int(big_int* polynomial, int N);

// target(x) = A(x) + B(x) * factor
void add_scaled_polynomial(
	const big_int* A, const big_int* B, int factor, 
	big_int* target, int N
);

// target(x) = A(x) * factor
void scale_polynomial(
	const big_int* A, int factor, 
	big_int* target, int N
);

// Implementations in file: src/polynomial.c