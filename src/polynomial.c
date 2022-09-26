#include <polynomial.h>

// *** Methods for polynomial arithmetics ***

// multiply by variable: polynomial(x) = x * polynomial(x)
void shift_right_big_int(big_int* polynomial, int N) {
	int len;
	for (len = N; len > 1 && big_int_equal(polynomial[len - 1], BIG_INT_ZERO); len--);
			

	for (int i = N - 1; i > 0; i--) 
		big_int_copy(polynomial[i], polynomial[i - 1]);
	
	// fprintf(stderr, "shifted: %d -> %d\n", len, len + 1); fflush(stderr);
	
	big_int_copy(polynomial[0], BIG_INT_ZERO);
}

// target(x) = A(x) + B(x) * factor
void add_scaled_polynomial(
	const big_int* A, const big_int* B, int factor, 
	big_int* target, int N
) {
	big_int z;
	for (int i = 0; i < N; i++) {
		big_int_small_mul(B[i], factor, z);
		big_int_add(A[i], z, target[i]);
	}
}

// target(x) = A(x) * factor
void scale_polynomial(
	const big_int* A, int factor, 
	big_int* target, int N
) {
	big_int z;
	for (int i = 0; i < N; i++)
		big_int_small_mul(A[i], factor, target[i]);
}