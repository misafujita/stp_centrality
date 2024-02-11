/*

dijkstra.c

Last-modified:JST<2024-02-12 00:51:43>

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "struct.h"
#include "emalloc.h"
#include "binaryheap.h"

void dijkstra(int N, node_t *alist, heap_t *heap, int *traversed, int *traversing, int start, double *dist, int *prev){

    int     i, j;
    int     heap_empty;
    int     now;
    int     to;
    double  cost;

    for(i=0;i<=N;i++){
		heap[i].value = 0;
		heap[i].index = 0;
		traversed[i]  = 0;
		traversing[i] = 0;
		dist[i]       = INT_MAX;
		prev[i]       = 0;
    }

    dist[start]   = 0;
    heap[1].value = 0;
    heap[1].index = start;
    heap_empty    = 2;

    while(heap_empty > 1){

		now = heap[1].index;
		min_dequeue(heap, &heap_empty);

		traversed[now] = 1;

		for(i=1;i<=alist[now].degree;i++){

			to   = alist[now].to[i];
			cost = dist[now] + alist[now].cost[i];

			if(traversed[to] == 1){ continue; }

			if(cost < dist[to]){

				if(traversing[to] == 0){

					dist[to] = cost;
					prev[to] = now;
					min_inqueue(heap, &heap_empty, cost, to);
					traversing[to] = 1;

				}else{

					for(j=1;j<heap_empty;j++){
						if(heap[j].index == to){
							if(cost < heap[j].value){
								dist[to] = cost;
								prev[to] = now;
								min_inqueue_overrap(heap, j, cost);
							}
						}
					}

				}

			}

		}

    }

}

void track_prev(int *prev, int start, int goal, int *tracked){

    int i;

    i          = goal;
    tracked[i] = 1;

    do{
		i          = prev[i];
		tracked[i] = 1;
    }while(i != start);

}
