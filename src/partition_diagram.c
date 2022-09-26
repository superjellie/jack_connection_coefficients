#include <partition_diagram.h>
#include <stdlib.h>

typedef struct partition_diagram_node pdnode;

// *** Partition diagram managment ***

// helper function in diagram creation
static pdnode* new_node(
	pdnode** node,
	int part, 
	int Y, 
	pdnode* children
) {
	(*node)->part = part;
	(*node)->num_of_children = Y == 0? 0 :
							 part <= Y / 2? Y / 2 - part + 2 : 1;
						
	int offset = part == 1? 0 :
	             part <= Y / 2? part - 1 : Y / 2;
	
	
	(*node)->children = children + offset;
	
	// actually here index_limit is number of partitions from this node
	(*node)->index_limit = Y == 0? 1 : 0;
	for (int i = 0; i < (*node)->num_of_children; i++) 
		(*node)->index_limit += (*node)->children[i].index_limit;
	
	pdnode* x = *node;
	*node = *node - 1;
	return x;
}

// creates new partition diagram
pdnode* new_partition_diagram(int N) {
	int size = N % 2 == 0? (N / 2) * (N / 2) + N + 1 :
						   (N / 2) * (N / 2) + 3 * (N / 2) + 2; 
	
	pdnode* diagram 
		= malloc(size * sizeof(pdnode));
		
	if (!diagram) return NULL;
	
	pdnode* node = diagram + (size - 1);
	
	pdnode* anchors[N];
	anchors[0] = new_node(&node, 1, 0, NULL);
	
	for (int i = 2; i <= N; i++) {
		new_node(&node, i, 0, NULL);
		for(int j = i / 2; j >= 2; j--) 
			new_node(&node, j, i - j, anchors[i - j - 1]);
		anchors[i - 1] = new_node(&node, 1, i - 1, anchors[i - 2]);
	}
	
	new_node(&node, 1, N, anchors[N - 1]);
	
	// calculate index_limit
	diagram->index_limit = 0;
	for (pdnode* anchor = diagram; anchor; anchor = anchor->children) {
		int cumulative_sum = 0;
		for (int i = 0; i < anchor->num_of_children; i++) {
			int l = anchor->children[i].index_limit;
			anchor->children[i].index_limit = cumulative_sum;
			cumulative_sum += l;
		} 
	}
	
	// calculate index_modifier
	for (int i = 0; i < size; i++) {
		diagram[i].index_modifier = diagram[i].num_of_children > 0?
			diagram[i].index_limit - diagram[i].children[0].index_limit :
			diagram[i].index_limit;
	}
		
	return diagram;
}

// frees memory
void delete_partition_diagram(pdnode* diagram) {
	free(diagram);
}

// prints diagram as graph in DOT language
// can be used by graphviz to display graph
// in project is used like:
// graph 10 | dot -Tsvg > output.svg
// where 10 is N for witch diagram is constructed
void print_partition_diagram_as_graph(
	pdnode* diagram
) {
	printf("digraph partition_diagram {\n");
	printf("rankdir=TB;\n");
	printf("node [shape=record];\n");
	
	int anchor_size = 1;
	for (pdnode* anchor = diagram; anchor; 
	     anchor = anchor->children) {
		printf("node_%p [label=\"", anchor);
		for (int i = 0; i < anchor_size; i++) {
			printf(
				"{<if%d> part: %d|children: %d|id_limit: %d|<of%d> id_mod: %d}", 
				i, anchor[i].part, 
				anchor[i].num_of_children,
				anchor[i].index_limit,
				i, anchor[i].index_modifier
			);
			if (i < anchor_size - 1) printf("|");
		}
		
		printf("\"];\n");
		for (int i = 0; i < anchor_size; i++)
			if (anchor[i].children != NULL) {
				int offset = anchor[i].num_of_children == 1?
								anchor[i].children[0].part / 2 :
								anchor[i].children[0].part - 1;
				printf(
					"node_%p:of%d -> node_%p:if%d;\n", 
					anchor, i, 
					anchor[i].children - offset, 
					offset
				);
			}
		anchor_size = anchor->num_of_children;
	} 
	
	printf("}\n");
}

// returns subdiagram that equivalent to diagram of K
pdnode* get_partition_diagram_anchor(pdnode* diagram, int K) {
	for (int i = 0; i < K; i++)
		diagram = diagram->children;
	return diagram;
}


// returns max index of partition of N
// (partition number p(N) - 1)
int get_partition_diagram_max_index(pdnode* diagram) {
	if (!diagram) return 0;
	if (!diagram->children) return 0;
	return diagram->children[diagram->num_of_children - 1].index_limit;
}

// *** Operations on partitions ***

// calculates partition index; complexety O(N)
int encode_partition(pdnode* diagram, int* partition, int len) {
	pdnode* node = diagram;
	int code = 0;
	for (int i = 0; i < len && node->children; i++) {
		code += node->index_modifier;
		int j = partition[i] - node->part >= node->num_of_children? 
				node->num_of_children - 1 :
				partition[i] - node->part;
		node = node->children + j;
		if (!node) {
			fprintf(stderr, "[encode] Zero node!\n");
			fflush(stderr);
		}
	}
	return code + node->index_modifier;
}

// calculates partition from index; complexety O(N ^ 2)
// can be improved to O(N * ln N)
void decode_partition(pdnode* diagram, int* partition, int* len, int code) {
	int l = 0;
	for (pdnode* node = diagram; node->children; ) {
		code -= node->index_modifier;
		int next = 0;
		for (; next < node->num_of_children - 1; next++)
			if (code < node->children[next + 1].index_limit) break;
		node = node->children + next;
		if (!node) {
			fprintf(stderr, "[decode] Zero node!\n");
			fflush(stderr);
		}
		if (l >= *len) {
			fprintf(stderr, "[decode] Incorrect partition code %d!\n", code);
			fflush(stderr);
		}
		
		partition[l] = node->part;
		l++;
	}
	*len = l;
}

