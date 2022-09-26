#pragma once

#include <stdio.h>

// partition diagram from "Efficient Data Structures for Storing the Partitions of Integers"

struct partition_diagram_node {
	int part;
	int num_of_children;
	int index_modifier; // these two fields are needed for
	int index_limit;    // encoding and decoding partitions from it's index
	
	struct partition_diagram_node* children;
};

typedef struct partition_diagram_node pdiagram;

// *** Partition diagram managment ***

// creates new partition diagram
pdiagram* new_partition_diagram(int N);

// frees memory
void delete_partition_diagram(pdiagram* diagram);

// prints diagram as graph in DOT language
// can be used by graphviz to display graph
// in project is used like:
// graph 10 | dot -Tsvg > output.svg
// where 10 is N for witch diagram is constructed
void print_partition_diagram_as_graph(pdiagram* diagram);

// returns subdiagram that equivalent to diagram of K
pdiagram* get_partition_diagram_anchor(pdiagram* diagram, int K);

// returns max index of partition of N
// (partition number p(N) - 1)
int get_partition_diagram_max_index(pdiagram* diagram);


// *** Operations on partitions ***

// calculates partition index; complexety O(N)
int encode_partition(pdiagram* diagram, int* partition, int len);

// calculates partition from index; complexety O(N ^ 2)
// can be improved to O(N * ln N)
void decode_partition(pdiagram* diagram, int* partition, int* len, int code);