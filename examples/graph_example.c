#include "graph.h"
#include "algorithm.h"
#include <stddef.h>
#include <stdlib.h>

void print_vertex(int v) 
{
    printf("Visited %d\n", v);
}


int main(void)
{
	Graph mygraph;

	init_graph(&mygraph, 15);

	int begin = 1;
	for (int i = 1; i <= 15; ++i)
	{
		if (begin == i)
			continue;

		add_edge(&mygraph, begin, i);

		if (i % 5 == 0)
			begin += 1;
	}

	bfs_graph(&mygraph, 1, print_vertex);
	puts("\n\n");
	bfs_graph(&mygraph, 2, print_vertex);
	puts("\n\n");
	bfs_graph(&mygraph, 3, print_vertex);
	
	free_graph(&mygraph);
	return 0;
}