#ifndef H_GRAPH
#define H_GRAPH

#include <stddef.h>
typedef struct GraphNode 
{
    int vertex;
    struct GraphNode *next;
} GraphNode;

typedef struct Graph
{
    size_t num_vertices;
    GraphNode **adj_lists;
} Graph;


void init_graph(Graph *graph, size_t num_vertices);
void add_edge(Graph *graph, int src, int dest);
bool has_edge(const Graph *graph, int src, int dest); 
GraphNode *get_neighbors(const Graph *graph, int vertex);
void remove_edge(Graph *graph, int src, int dest);
void free_graph(Graph *graph);

#endif