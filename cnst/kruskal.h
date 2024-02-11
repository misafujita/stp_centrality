#ifndef KRUSKAL_H_DEFINE
#define KRUSKAL_H_DEFINE

void quicksort_edge(edge_t *array, int begin, int end);

int  root(int *par, int x);

void unite(int *par, int x, int y);

void kruskal(int N, int E, edge_t *graph, int *par, edge_t *mst, double *mst_cost);

void c_kruskal(int N, int E, edge_t *elist, int *par, st_t *st);

int num_cmp(int N, int *frag, int *par, int *node);

#endif
