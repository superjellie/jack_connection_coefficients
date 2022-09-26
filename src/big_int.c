#include <big_int.h>

const big_int BIG_INT_OVERFLOW = {[0 ... BIG_INT_SIZE - 1] = -1}; 
// const big_int BIG_INT_MAX      = {[0 ... BIG_INT_SIZE - 2] = -1, -2}; 
const big_int BIG_INT_ZERO     = {}; 
const big_int BIG_INT_ONE      = {1}; 

// adds two big_ints: result = x + y
void big_int_add(
	const BIG_INT_HALF* x, const BIG_INT_HALF* y,
	BIG_INT_HALF* result
) {
	BIG_INT_WORD z = 0;
	BIG_INT_HALF carry = 0;
	
	for (int i = 0; i < BIG_INT_SIZE; i++) {
		z = (BIG_INT_WORD)x[i] + (BIG_INT_WORD)y[i] + (BIG_INT_WORD)carry;
		result[i] = (BIG_INT_HALF)z;
		carry     = (BIG_INT_HALF)(z >> BIG_INT_HALF_LEN);
	}
	
	if (carry > 0) 
		for (int i = 0; i < BIG_INT_SIZE; i++) 
			result[i] = BIG_INT_OVERFLOW[i];
}

// multiplies big_int by small number
// result = x * y
void big_int_small_mul(
	const BIG_INT_HALF* x, BIG_INT_HALF y,
	BIG_INT_HALF* result
) {
	BIG_INT_WORD z = 0;
	BIG_INT_HALF carry = 0;
	
	for (int i = 0; i < BIG_INT_SIZE; i++) {
		z = (BIG_INT_WORD)x[i] * (BIG_INT_WORD)y + (BIG_INT_WORD)carry;
		result[i] = (BIG_INT_HALF)z;
		carry     = (BIG_INT_HALF)(z >> BIG_INT_HALF_LEN);
	}
	
	if (carry > 0) 
		for (int i = 0; i < BIG_INT_SIZE; i++) 
			result[i] = BIG_INT_OVERFLOW[i];
}

// test two big_ints on equality
bool big_int_equal(
	const BIG_INT_HALF* x, 
	const BIG_INT_HALF* y
) {
	for (int i = 0; i < BIG_INT_SIZE; i++)
		if (x[i] != y[i]) return false;
	return true;
}

// assigment for big_ints
void big_int_copy(
	BIG_INT_HALF* dst,
	const BIG_INT_HALF* src
) {
	for (int i = BIG_INT_SIZE - 1; i >= 0; i--) 
		dst[i] = src[i];
}

// prints big int with format specified in <big_int_defs.h>
void fprintf_big_int(FILE* out, const BIG_INT_HALF* x) {
	if (big_int_equal(x, BIG_INT_OVERFLOW)) {
		fprintf(out, BIG_INT_OVERFLOW_PRI);
		return;
	}
	for (int i = BIG_INT_SIZE - 1; i >= 0; i--) 
		fprintf(out, BIG_INT_HALF_PRI, x[i]); 
}


