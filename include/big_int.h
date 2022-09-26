#pragma once

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>

// *** Big integers ***

// this defs define size of big_int
#include <big_int_defs.h>

// big_int is an array of BIG_INT_HALF 
// with size BIG_INT_SIZE
typedef BIG_INT_HALF big_int[BIG_INT_SIZE];

extern const big_int BIG_INT_OVERFLOW; 
// extern const big_int BIG_INT_MAX; 
extern const big_int BIG_INT_ZERO; 
extern const big_int BIG_INT_ONE; 

// adds two big_ints: result = x + y
void big_int_add(
	const BIG_INT_HALF* x, const BIG_INT_HALF* y,
	BIG_INT_HALF* result
);

// multiplies big_int by small number
// result = x * y
void big_int_small_mul(
	const BIG_INT_HALF* x, BIG_INT_HALF y,
	BIG_INT_HALF* result
);

// test two big_ints on equality
bool big_int_equal(
	const BIG_INT_HALF* x, 
	const BIG_INT_HALF* y
);

// assigment for big_ints
void big_int_copy(
	BIG_INT_HALF* dst,
	const BIG_INT_HALF* src
);

// prints big int with format specified in <big_int_defs.h>
void fprintf_big_int(FILE* out, const BIG_INT_HALF* x);

