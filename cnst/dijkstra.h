#ifndef DIJKSTRA_H_DEFINE
#define DIJKSTRA_H_DEFINE

void dijkstra(int N, node_t *alist, heap_t *heap, int *traversed, int *traversing, int start, double *dist, int *prev);

void track_prev(int *prev, int start, int goal, int *tracked);

#endif
