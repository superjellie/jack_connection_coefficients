#pragma once

// *** Methods for arithmetics on partitions ***

// Partitions are sorted arrays of int in ascending order:
// [1, 1, 2, 4, 4, 4, 7]
// indexed from 0.

// shift partition left:
// shift_left([3, 5, 8, 9]) == [5, 8, 9] 
void shift_left(int* partition, int N);

// shift partition right:
// shift_right([3, 5, 8, 9]) == [0, 3, 5, 8, 9] 
// (what we get is not exactly partition)
void shift_right(int* partition, int N);

// partition \ {partition[0]} U {partition[0] - 1}
// drop_by_0th_part([2, 4, 6]) = [1, 4, 6]
// drop_by_0th_part([1, 4, 6]) = [4, 6]
int drop_by_0th_part(int* partition, int len);

// partition \ {partition[0], partition[j]} U {partition[0] + partition[j] - 1}
// double_drop_by_0th_and_jth([2, 4, 6], 1) = [5, 6]
// double_drop_by_0th_and_jth([2, 4, 6], 2) = [4, 7]
int double_drop_by_0th_and_jth(int* partition, int len, int j);

// partition \ {partition[0]} U {partition[0] - 1 - d, d}
// complex_rise([4, 6], 1) = [1, 2, 5, 6]
int complex_rise(int* partition, int len, int d);
