#include <partition_diagram.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	int N = atoi(argv[1]);
	
	struct partition_diagram_node* diagram 
		= new_partition_diagram(N);
	print_partition_diagram_as_graph(diagram);
	delete_partition_diagram(diagram);
	return 0;
}