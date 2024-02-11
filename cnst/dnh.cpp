/*

dnh.c

*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "emalloc.h"
#include "swap.h"
#include "dijkstra.h"
#include "kruskal.h"

void quicksort_edge_ind(edge_t *array, int begin, int end){

    int    i = begin;
    int    j = end;
    double pivot;

    pivot = array[ ( begin + end ) / 2 ].from;

    while(1){

		while( array[i].from < pivot ){ ++i; }
		while( array[j].from > pivot ){ --j; }
		if( i >= j ){ break; }

		swap_int(&array[i].from, &array[j].from);
		swap_int(&array[i].to, &array[j].to);
		swap_dbl(&array[i].cost, &array[j].cost);

		i++;
		j--;

    }

    if( begin < i - 1 ){ quicksort_edge_ind( array, begin, i-1 ); }
    if( j + 1 < end ){ quicksort_edge_ind( array, j+1, end ); }

}

void dnh(int N, int E, int T, edge_t *elist, node_t *alist, int *trmnl, frag_t *frag, int *parent, st_t *st){

    int     i, j, k;
    int     E_cmp;
    edge_t *elist_cmp;
    heap_t *heap;
    double *dist;
    int    *prev;
    edge_t *mst_cmp;
    double  mst_cost;

    E_cmp = (T * T - T) / 2;

    elist_cmp = (edge_t*)e_malloc(E_cmp+1, sizeof(edge_t), "elist_cmp");
    heap      = (heap_t*)e_malloc(N+1, sizeof(heap_t), "heap");
    dist      = (double*)e_malloc(N+1, sizeof(double), "dist");
    prev      = (int*)e_malloc(N+1, sizeof(int), "prev");

    k = 1;
    for(i=1;i<=T;i++){

		dijkstra(N, alist, heap, frag->a, frag->b, trmnl[i], dist, prev);

		for(j=i+1;j<=T;j++){
			elist_cmp[k].from = i;
			elist_cmp[k].to   = j;
			elist_cmp[k].cost = dist[ trmnl[j] ];
			k++;
		}

    }

    mst_cmp = (edge_t*)e_malloc(T, sizeof(edge_t), "mst_cmp");

    quicksort_edge(elist_cmp, 1, E_cmp);
    kruskal(T, E_cmp, elist_cmp, parent, mst_cmp, &mst_cost);

    for(i=1;i<=N;i++){ st->node[i] = 0; }

    quicksort_edge_ind(mst_cmp, 1, T-1);

    i = 1;
    j = -1;
    while(i <= T-1){

		if(j != mst_cmp[i].from){
			j = mst_cmp[i].from;
			dijkstra(N, alist, heap, frag->a, frag->b, trmnl[j], dist, prev);
		}

		track_prev(prev, trmnl[ mst_cmp[i].from ], trmnl[ mst_cmp[i].to ], st->node);

		i++;
    }

    c_kruskal(N, E, elist, parent, st);

    free(elist_cmp);
    free(heap);
    free(dist);
    free(prev);
    free(mst_cmp);

}
