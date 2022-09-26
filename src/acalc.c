#include <stdlib.h>
#include <string.h>
#include <partition_diagram.h>
#include <big_int.h>
#include <polynomial.h>
#include <partition.h>
#include <time.h>

#ifdef BINARY
void print_polynom(big_int* polynom, int N) {
	fwrite(polynom, sizeof(big_int), N, stdout);
	fflush(stdout);
}

void print_partition(FILE* out, int* partition, int N, int W) {
	int zeros[W]; for (int i = 0; i < W; i++) zeros[i] = 0;
	fwrite(partition, sizeof(int), N, out);
	fwrite(zeros, sizeof(int), W, out);
	fflush(out);
}
#else
void print_polynom(big_int* polynom, int N) {
	for (int i = 0; i < N; i++) {
		fprintf_big_int(stdout, polynom[i]); 
		printf(" ");
	}
	printf("\n"); fflush(stdout);
}

void print_partition(FILE* out, int* partition, int N, int W) {
	fprintf(out, "[");
	for (int i = 0; i < N; i++) 
		fprintf(out, "%3d", partition[i]);
	
	fprintf(out, "]"); 
	
	for (int i = N; i < W; i++)
		fprintf(out, "   ");
	
	fflush(out);
}
#endif


// Calculates jack connection coefficients for partitions of N
// Can't do much about how long formulas looks like in C :(
void calculate_for_N(
	big_int* jccs,
	int N, int K,
	pdiagram* diagram
) {
	// In calculation we use fact, that all operations
	// on partitions drop their sum by one
	
	// Therefore we can calculate firstly for all partitions,
	// that starts not with one (with indexes from [m, M)): 
	// they will reuse first part of array from [0, m) that already 
	// contains calculated coefficients for partitions of N - 1
	
	int m = get_partition_diagram_max_index(diagram->children) + 1;
	int M = get_partition_diagram_max_index(diagram) + 1;
	
	// 
	int partition[N];
	int mod_partition[N];
	big_int third_summand[N];
	for (int i = 0; i < N; i++)
		big_int_copy(third_summand[i], BIG_INT_ZERO);
	int len = 0;
	int new_len = 0;
	//
	
	for (int code = m; code < M; code++) {
		big_int* target_jcc = jccs + code * N;
		for(int i = 0; i < N; i++) 
			big_int_copy(target_jcc[i], BIG_INT_ZERO);
		
		len = N;
		decode_partition(diagram, partition, &len, code);
		print_partition(stdout, partition, len, N);
		
		memcpy(mod_partition, partition, len * sizeof(int));
		new_len = drop_by_0th_part(mod_partition, len);
		
		// first summand (with x)
		int dropped_code 
			= encode_partition(diagram->children, mod_partition, new_len);
		big_int* dropped_jcc = jccs + dropped_code * N;
		
		add_scaled_polynomial(
			target_jcc, dropped_jcc, partition[0] - 1, target_jcc, N
		);
		
		// third summand (with x)
		for (int j = 1; j < len; j++) {
			memcpy(mod_partition, partition, len * sizeof(int));
			new_len = double_drop_by_0th_and_jth(mod_partition, len, j);
			int double_dropped_code 
				= encode_partition(diagram->children, mod_partition, new_len);
			big_int* double_dropped_jcc = jccs + double_dropped_code * N;
		
			add_scaled_polynomial(
				third_summand, double_dropped_jcc, partition[j],
				third_summand, N
			);
		}
		
		add_scaled_polynomial(
			target_jcc, third_summand, 1, target_jcc, N
		);
		
		
		// shift by x
		shift_right_big_int(target_jcc, N);
		
		// second summand (without x)
		for (int d = 1; d <= partition[0] - 2; d++) {
			memcpy(mod_partition, partition, len * sizeof(int));
			new_len = complex_rise(mod_partition, len, d);
			int rised_code 
				= encode_partition(diagram->children, mod_partition, new_len);
			big_int* rised_jcc = jccs + rised_code * N;
			
			add_scaled_polynomial(
				target_jcc, rised_jcc, 1, target_jcc, N
			);
		}
		
		// third summand (without x)
		add_scaled_polynomial(
			target_jcc, third_summand, 1, target_jcc, N
		);
		
		print_polynom(target_jcc, N);
	} 
	
	// after we done with coefficients with indices from [m, M)
	// we use short formula to recalculate coefficients [0, m)
	// (formula with partition[0] = 1)
	for (int code = 0; code < m; code++) {
		big_int* target_jcc = jccs + code * N;
		len = N;
		decode_partition(diagram, partition, &len, code);
		print_partition(stdout, partition, len, N);
		
		scale_polynomial(target_jcc, K - 1, target_jcc, N);
		
		for (int i = 0; i < N; i++)
			big_int_copy(third_summand[i], target_jcc[i]);
		
		shift_right_big_int(target_jcc, N);
		add_scaled_polynomial(
			target_jcc, third_summand, 1, target_jcc, N
		);
		
		print_polynom(target_jcc, N);
	}
}


int main(int argc, char** argv) {
	
	if (argc != 2 || strcmp(argv[1], "help") == 0) {
		fprintf(stderr, "USAGE: %s [N]\n", argv[0]); 
		fprintf(stderr, "This program prints jack connection coefficients\n", argv[0]); 
		fprintf(stderr, "in special case [partition of i, {i}, {i}]\n"); 
		fprintf(stderr, "for all partitions of i, for any i from 2 to N >= 2.\n"); 
		fprintf(stderr, "To output in [filename] use pipes: %s [n] > [filename]\n", argv[0]); 
		fflush(stderr);
		return -1;
	}
	
	clock_t clock_1 = clock();
	int N = atoi(argv[1]);
	
	// partition diagram
	pdiagram* diagram = new_partition_diagram(N);
	
	if (!diagram) {
		fprintf(stderr, "Couldn't create partition diagram\n"); fflush(stderr);
		return -1;
	}
	
	int M = get_partition_diagram_max_index(diagram) + 1;
	
	// jack connection coefficients
	big_int* jccs = calloc(N * M, sizeof(big_int));
	
	if (!jccs) {
		fprintf(stderr, "Memmory cannot be allocated [%d B]\n", N * M * sizeof(big_int)); fflush(stderr);
		return -1;
	}
	

	// init with N = 1
	big_int_copy(jccs[0], BIG_INT_ONE);
	
	#ifdef BINARY
	int header[8] = {N, M, sizeof(BIG_INT_HALF), sizeof(BIG_INT_SIZE)};
	fwrite(&header, sizeof(int), 8, stdout);
	#endif
	
	for (int K = 2; K <= N; K++) 
		calculate_for_N(jccs, N, K, get_partition_diagram_anchor(diagram, N - K));
	
	free(jccs);
	delete_partition_diagram(diagram);
	
	clock_t clock_2 = clock();
	fprintf(stderr, "Done [%lf s].\n", (double)((clock_2 - clock_1) / CLOCKS_PER_SEC)); fflush(stderr);
	return 0;
}