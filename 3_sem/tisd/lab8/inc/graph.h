#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#define INF 1000000

typedef int **graph_t;

int **input_graph(int *n);
int **read_graph_from_file(FILE *file, int *n);

void print_adjacency_matrix(graph_t graph, int n);
void save_to_png_from_graphviz(graph_t graph, int n);

void find_reachable_vertices(graph_t graph, int n, int start, int max_distance);

void free_graph(graph_t graph, int n);

#endif//MATRIX_GRAPH_H
