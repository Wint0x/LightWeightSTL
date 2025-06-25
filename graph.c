#include "graph.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>


void init_graph(Graph *graph, size_t num_vertices) 
{
    graph->num_vertices = num_vertices;
    graph->adj_lists = calloc(num_vertices, sizeof(GraphNode*));
    if (!graph->adj_lists) return;

}

void add_edge(Graph *graph, int src, int dest) 
{
	if (!graph || src >= graph->num_vertices || dest >= graph->num_vertices) return;

	GraphNode* new_node = malloc(sizeof(GraphNode));
	if (!new_node) return; // or handle error

    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;
}

bool has_edge(const Graph *graph, int src, int dest) 
{
    if (!graph || src >= graph->num_vertices || dest >= graph->num_vertices) return false;

    GraphNode *temp = graph->adj_lists[src];
    while (temp) 
    {
        if (temp->vertex == dest) return true;
        temp = temp->next;
    }
    return false;
}

GraphNode *get_neighbors(const Graph *graph, int vertex) 
{
    if (!graph || vertex >= graph->num_vertices) return NULL;
    return graph->adj_lists[vertex];  // Caller should NOT free this
}


void remove_edge(Graph *graph, int src, int dest) 
{
    if (!graph || src >= graph->num_vertices) return;

    GraphNode *current = graph->adj_lists[src];
    GraphNode *prev = NULL;

    while (current) {
        if (current->vertex == dest) 
        {
            if (prev)
                prev->next = current->next;
            else
                graph->adj_lists[src] = current->next;

            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void free_graph(Graph *graph) 
{
    for (size_t v = 0; v < graph->num_vertices; ++v) 
    {
        GraphNode* curr = graph->adj_lists[v];
        while (curr) 
        {
            GraphNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->adj_lists);
    graph->adj_lists = NULL;
    graph->num_vertices = 0;
}
