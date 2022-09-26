// Test for encoding and decoding
#include <partition_diagram.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int N = 20;
	int M = 627;
	struct partition_diagram_node* diagram 
		= new_partition_diagram(N);
	
	
	int partition[N + 1];
	int len = 0;
	printf("N = %d, M = %d, diagram = %p\n", N, M, diagram);
	
	for (int i = 0; i < M; i++) {
		decode_partition(diagram, partition, &len, i);
		int code = encode_partition(diagram, partition, len);
		printf("%2d|%2d: ", i, code);
		for (int k = 0; k < len; k++) {
			printf("%2d ", partition[k]);
		}
		printf("\n");
	}
		
		
	delete_partition_diagram(diagram);
	return 0;
}