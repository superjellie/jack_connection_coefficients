#include <partition.h>

// *** Methods for arithmetics on partitions ***

// Partitions are sorted arrays of int in ascending order:
// [1, 1, 2, 4, 4, 4, 7]
// indexed from 0.

// shift partition left:
// shift_left([3, 5, 8, 9]) == [5, 8, 9] 
void shift_left(int* partition, int N) {
	for (int i = 0; i < N - 1; i++) 
		partition[i] = partition[i + 1];
	partition[N - 1] = 0;
}

// shift partition right:
// shift_right([3, 5, 8, 9]) == [0, 3, 5, 8, 9] 
// (what we get is not exactly partition)
void shift_right(int* partition, int N) {
	for (int i = N - 1; i > 0; i--) 
		partition[i] = partition[i - 1];
	partition[0] = 0;
}

// partition \ {partition[0]} U {partition[0] - 1}
// drop_by_0th_part([2, 4, 6]) = [1, 4, 6]
// drop_by_0th_part([1, 4, 6]) = [4, 6]
int drop_by_0th_part(int* partition, int len) {
	if (partition[0] > 1) {
		partition[0] -= 1;
		return len;
	}
	shift_left(partition, len);
	return len - 1;
}

// partition \ {partition[0], partition[j]} U {partition[0] + partition[j] - 1}
// double_drop_by_0th_and_jth([2, 4, 6], 1) = [5, 6]
// double_drop_by_0th_and_jth([2, 4, 6], 2) = [4, 7]
int double_drop_by_0th_and_jth(int* partition, int len, int j) {
	partition[0] = partition[0] + partition[j] - 1;
	shift_left(partition + j, len - j);
	
	for (int i = 0; partition[i] > partition[i + 1] && i + 1 < len - 1; i++) {
		int x = partition[i];
		partition[i] = partition[i + 1];
		partition[i + 1] = x;
	}
	
	return len - 1;
}

// partition \ {partition[0]} U {partition[0] - 1 - d, d}
// complex_rise([4, 6], 1) = [1, 2, 5, 6]
int complex_rise(int* partition, int len, int d) {
	int l0 = partition[0];
	shift_right(partition, len);
	partition[0] = d < l0 - 1 - d? d : l0 - 1 - d;
	partition[1] = d < l0 - 1 - d? l0 - 1 - d : d;
	return len + 1;
}
