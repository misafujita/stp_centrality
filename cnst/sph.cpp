/*

sph.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "struct.h"
#include "mersenne.h"
#include "emalloc.h"
#include "dijkstra.h"
#include "kruskal.h"

void sph(int N, int E, int T,edge_t *elist,  node_t *alist, int *trmnl, frag_t *frag, int *parent, st_t *st){

    int    i, j, t;
    int    source;
    double min;
    int    from_ind;
    int    from_vtx;
    int    to;

    heap_t  *heap;
    double  *dist;
    int     *prev;
    double **dists;
    int    **prevs;


    heap  = (heap_t*)e_malloc(N+1, sizeof(heap_t), "heap");
    dist  = (double*)e_malloc(N+1, sizeof(double), "dist");
    prev  = (int*)e_malloc(N+1, sizeof(int), "prev");
    dists = (double**)e_malloc(T+1, sizeof(double*), "dists");
    prevs = (int**)e_malloc(T+1, sizeof(int*), "prevs");
    for(i=0;i<=T;i++){
		dists[i] = (double*)e_calloc(N+1, sizeof(double), "dists[i]");
		prevs[i] = (int*)e_calloc(N+1, sizeof(int), "prevs[i]");
    }

    for(i=0;i<=T;i++){
		dijkstra(N, alist, heap, frag->a, frag->b, trmnl[i], dist, prev);

		for(j=1;j<=N;j++){
			dists[i][j] = dist[j];
			prevs[i][j] = prev[j];
		}
    }


    /*** Shortest Path Heuristic ***/
    for(i=1;i<=N;i++){
		st->node[i] = 0;
		frag->a[i]  = 0;
    }

    source = trmnl[ (int)(genrand_real1() * (T-1) + 0.5) + 1 ];

    st->node[ source ] = 1;

    t = 2;
    while(t <= T){

		min = INT_MAX;
		for(i=1;i<=T;i++){
			if(st->node[ trmnl[i] ] == 1){ continue; }
			for(j=1;j<=N;j++){
				if(st->node[j] == 0){ continue; }
				if(dists[i][j] > 0 && min > dists[i][j]){
					min   = dists[i][j];
					from_ind = i;
					from_vtx = trmnl[i];
					to       = j;
				}
			}
		}

		track_prev(prevs[ from_ind ], from_vtx, to, st->node);

		t++;

    }

    c_kruskal(N, E, elist, parent, st);


    for(i=0;i<=T;i++){
		free(dists[i]);
		free(prevs[i]);
    }
    free(heap);
    free(dist);
    free(prev);
    free(dists);
    free(prevs);

}
